#include <iostream>
#include <cstdlib>
#include <cmath>


/// Poisson + Gaussian fitting (PMT)
double response(double *x, double *p)
{

	// input x
	double xin = x[0];


	// parameters to fit
	double m0 = p[0];
	double sigma0 = p[1];
	double gain = p[2];
	double sigma = p[3];
	double mu = p[4];
	double norm = p[5];

	double val = 0.0;
	int N = 5;
	for(int n = 0; n < N; n++)
	{
		val += p[5]*(TMath::Exp(-p[4])*(TMath::Power(p[4],n))/TMath::Factorial(n))*TMath::Gaus(x[0],p[0]+n*p[2],TMath::Sqrt(n*p[3]*p[3]+p[1]*p[1]),kTRUE);
	}

	return val;
}


/// Several Gaussian fitting (MPPC)
double response1(double *x, double *p)
{

	// input x
	double xin = x[0];


	// parameters to fit
	double m0 = p[0];
	double sigma0 = p[1];
	double gain = p[2];
	double sigma = p[3];
	double mu = p[4];
	double norm = p[5];

	double val = 0.0;
	int N = 14; // 14 // number of photons including pedestal (maximum 14 photons)
	for(int n = 0; n < N; n++)
	{
		val += p[5+n]*TMath::Gaus(x[0],p[0]+n*p[2],TMath::Sqrt(n*p[3]*p[3]+p[1]*p[1]),kTRUE);
	}

	return val;
}

/// Invivisual response of photon (P + G fitting) 
double r(double *x, double *p)
{
	// input x
	double xin = x[0];


	// parameters to fit
	double m0 = p[0];
	double sigma0 = p[1];
	double gain = p[2];
	double sigma = p[3];
	double mu = p[4];
	double norm = p[5];
	double n = p[6];

	return p[5]*(TMath::Exp(-p[4])*(TMath::Power(p[4],p[6]))/TMath::Factorial(p[6]))*TMath::Gaus(x[0],p[0]+p[6]*p[2],TMath::Sqrt(p[6]*p[3]*p[3]+p[1]*p[1]),kTRUE);
}

/// Indivisual response of photon (Several G fitting)
double r100(double *x, double *p)
{
	// input x
	double xin = x[0];


	// parameters to fit
	double m0 = p[0];
	double sigma0 = p[1];
	double gain = p[2];
	double sigma = p[3];
	double mu = p[4];
	double norm = p[5];
	double n = p[6];

	return p[5]*TMath::Gaus(x[0],p[0]+p[6]*p[2],TMath::Sqrt(p[6]*p[3]*p[3]+p[1]*p[1]),kTRUE);
}

/// Output data reading and fitting
void result()
{
    TFile *input = new TFile("Run0030.root","read");

/////////////////////////////////////////////////////////////
///////////////////// FILE INFORMATION //////////////////////
/// Run0000.root, Run0001.root -> Pedestal, 3.200V to LED ///
/// Run0010.root, Run0011.root -> Pedestal, 3.250V to LED ///
/// Run0020.root, Run0021.root -> Pedestal, 3.300V to LED ///
/// Run0030.root, Run0031.root -> Pedestal, 3.350V to LED ///
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
	TCanvas *l1 = new TCanvas("Run0030 ped");
    TTree *tree = (TTree*)input->Get("tree");

    short y[15];

    tree->SetBranchAddress("adc",&y);

    TH1I *hist = new TH1I("hist","hist",150,100,250);

    int entries = tree->GetEntries();
    for(int i = 0; i < entries; i++)
    {
        tree->GetEntry(i);
        hist->Fill(y[1]); // connected to adc[1] 
    }
	// hist->SetTitle("Histogram");
	// hist->Draw();
	// hist->GetXaxis()->SetTitle("One channel correspond to 100 pC");
	// hist->GetYaxis()->SetTitle("Number of Events");

/// Poisson + Gaussian 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


	// TCanvas *l1 = new TCanvas();
	// TF1 *res_fit = new TF1("f", response,100,250,6);
	// res_fit->SetParNames("ped mean","ped std","gain","std","Mean of Npe","normalization const","norm");
	// res_fit->SetNpx(10000);

    // double a1 = 117.0;
	// double a2 = 2.0;
	// double a3 = 4.0;
    // double a4 = 1.0;
	// double a5 = 1.0;
	// double a6 = 10000.0;

	// res_fit->SetParameters(a1,a2,a3,a4,a5,a6);
	// res_fit->SetParLimits(0, 100, 130);
	// res_fit->SetParLimits(1, 1, 3);
	// res_fit->SetParLimits(2, 4, 7);
	// res_fit->SetParLimits(3, -1.5, 1.5);
	// res_fit->SetRange(110,140);

	// hist->Fit(res_fit,"R");
	// hist->SetTitle("Histogram");
	// hist->Draw();
	// hist->GetXaxis()->SetTitle("One channel correspond to 100 pC");
	// hist->GetYaxis()->SetTitle("Number of Events");

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Several Gaussians
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

	// TF1 *res_fit = new TF1("f", response1,100,250,20);
	// res_fit->SetNpx(10000);

    // double a1 = 117.0;
	// double a2 = 2.0;
	// double a3 = 4.0;
    // double a4 = 2.0;
	// double a5 = 1.0;
	// double a6 = 1000.0;
	// double a7 = 1000.0;
	// double a8 = 1000.0;
	// double a9 = 1000.0;
	// double a10 = 1000.0;
	// double a11 = 1000.0;
	// double a12 = 1000.0;
	// double a13 = 1000.0;
	// double a14 = 1000.0;
	// double a15 = 1000.0;
	// double a16 = 1000.0;
	// double a17 = 1000.0;
	// double a18 = 1000.0;
	// double a19 = 1000.0;
	// double a20 = 1000.0;

	// res_fit->SetParameter(0,a1);
	// res_fit->SetParameter(19,a20);
	// res_fit->SetParLimits(0, 100, 130);
	// res_fit->SetParLimits(1, 0.1, 3);
	// res_fit->SetParLimits(2, 3, 10);
	// // res_fit->SetParLimits(3,-2.0, 2.0);
	// res_fit->SetParLimits(3, -2, 3);
	// res_fit->SetRange(110,200); // 110 ~ 200


	// hist->Fit(res_fit,"R");
	hist->SetTitle("Histogram");
	hist->Draw();
	hist->GetXaxis()->SetTitle("One channel correspond to 100 fC");
	hist->GetYaxis()->SetTitle("Number of Events");


/// Fitting process up to five photon response
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


    // double c0 = res_fit->GetParameter(0);
    // double c1 = res_fit->GetParameter(1);
    // double c2 = res_fit->GetParameter(2);
    // double c3 = res_fit->GetParameter(3);
    // double c4 = res_fit->GetParameter(4);
    // double c5 = res_fit->GetParameter(5);
    // double c6 = res_fit->GetParameter(6);
    // double c7 = res_fit->GetParameter(7);
    // double c8 = res_fit->GetParameter(8);
    // double c9 = res_fit->GetParameter(9);
    // double c10 = res_fit->GetParameter(10);
    
    // // cout << c0 << endl; // check fitting parameters
    // // cout << c1 << endl;
    // // cout << c2 << endl;
    // // cout << c3 << endl;
    // // cout << c4 << endl;
    // // cout << c5 << endl;

    // TF1 *r1 = new TF1("r1",r100,100,250,7);r1->SetNpx(1000);
	// TF1 *r2 = new TF1("r2",r100,100,250,7);r2->SetNpx(1000);
	// TF1 *r3 = new TF1("r3",r100,100,250,7);r3->SetNpx(1000);
	// TF1 *r4 = new TF1("r4",r100,100,250,7);r4->SetNpx(1000);
	// TF1 *r5 = new TF1("r5",r100,100,250,7);r5->SetNpx(1000);
	// TF1 *r6 = new TF1("r6",r100,100,250,7);r6->SetNpx(1000);

	// r1->SetParameters(c0,c1,c2,c3,c4,c5,0);
	// r2->SetParameters(c0,c1,c2,c3,c4,c6,1);
	// r3->SetParameters(c0,c1,c2,c3,c4,c7,2);
	// r4->SetParameters(c0,c1,c2,c3,c4,c8,3);
	// r5->SetParameters(c0,c1,c2,c3,c4,c9,4);
	// r6->SetParameters(c0,c1,c2,c3,c4,c10,5);

	// hist->SetTitle("Histogram");
	// r1->Draw("lsame");
	// r1->SetLineColor(3);
	// r2->Draw("lsame");
	// r2->SetLineColor(7);
	// r3->Draw("lsame");
	// r3->SetLineColor(5);
	// r4->Draw("lsame");
	// r4->SetLineColor(6);
	// r5->Draw("lsame");
	// r5->SetLineColor(8);
	// r6->Draw("lsame");
	// r6->SetLineColor(9);

	// auto legend = new TLegend(0.6,0.5,0.98,0.75);
	// legend->SetHeader("Separate photon response","C");
    // legend->AddEntry(r1,"pedestal");
    // legend->AddEntry(r2,"one photon");
    // legend->AddEntry(r3,"two photon");
	// legend->AddEntry(r4,"three photon");
	// legend->AddEntry(r5,"four photon");
	// legend->AddEntry(r6,"five photon");
    // legend->Draw();
    

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

}
