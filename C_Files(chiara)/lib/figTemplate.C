/** questa libreria ha il solo scopo di raccogliere le funzioni per disegnare
 * i grafici in maniera più rapida e compatta nel codice. */
#ifndef FIGTEMPLATE_H
#define FIGTEMPLATE_H

#include "Rtypes.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TGraph.h"

//******************************************************************************
// Histogram ----------
//******************************************************************************
void initFigTemplate()
{
    gStyle->SetPalette(kRainBow);    // arriva fino al rosso nei grafici 2d
    gStyle->SetPadLeftMargin(0.13);  // evita che le etichedde degli assi y vengano tagliate
    gStyle->SetPadRightMargin(0.13); // evita che le etichedde degli assi y vengano tagliate
}

/**supported options:
 * pe, logx, logy, nostat, stat1 */
void drawH(Int_t NPad, TH1 *hist,
           const char *xLabel = "not set",
           const char *yLabel = "not set",
           TString options = "hist")
{
    TCanvas *c = (TCanvas *)gROOT->GetListOfCanvases()->Last();
    c->cd(NPad);

    TString drawOpt = "";
    options.Append(" ");  // serve per "regolarizzare" la stringa
    options.Prepend(" "); // serve per "regolarizzare" la stringa

    // draw options ************************************************************
    hist->SetMarkerSize(0.7);
    hist->SetMarkerStyle(20);
    if (options.Contains(" pe "))
        drawOpt.Append("pe ");

    // layout options **********************************************************
    if (options.Contains(" logx "))
        c->GetPad(NPad)->SetLogx();
    if (options.Contains(" logy "))
        c->GetPad(NPad)->SetLogy();
    if (options.Contains(" nostat "))
        hist->SetStats(0);
    if (options.Contains(" stat1 ")) // to see entries only
        gStyle->SetOptStat(1);
    if (options.Contains(" statFlow ")) // toverflow and underflow
        gStyle->SetOptStat(111111);

    // axes ********************************************************************
    hist->GetXaxis()->SetTitle(xLabel);
    hist->GetYaxis()->SetTitle(yLabel);

    hist->DrawCopy(drawOpt);

    // salvataggio su fileI
    if (options.Contains(" eps "))
        c->SaveAs(Form("fig/%s.eps", hist->GetName()));
}

void drawH2D(Int_t NPad, TH2 *hist,
             const char *xLabel = "not set",
             const char *yLabel = "not set",
             TString options = "colz")
{
    TString drawOpt = "";
    options.Append(" ");  // serve per "regolarizzare" la stringa
    options.Prepend(" "); // serve per "regolarizzare" la stringa

    // last active canvas:
    TCanvas *c = (TCanvas *)gROOT->GetListOfCanvases()->Last();
    c->cd(NPad);

    // draw options ************************************************************
    if (options.Contains(" colz "))
        drawOpt.Append("colz ");

    // layout options **********************************************************
    if (options.Contains(" logx "))
        c->SetLogx();
    if (options.Contains(" logy "))
        c->SetLogy();
    if (options.Contains(" logz "))
        c->SetLogz();
    if (options.Contains(" nostat "))
        hist->SetStats(0);

    // axes ********************************************************************
    hist->GetXaxis()->SetTitle(xLabel);
    hist->GetYaxis()->SetTitle(yLabel);

    hist->DrawCopy(drawOpt);

    // salvataggio su fileI
    if (options.Contains(" eps "))
        c->SaveAs(Form("fig/%s.eps", hist->GetName()));
}

//******************************************************************************
// GraphError ----------
//******************************************************************************

void drawG(Int_t NPad, TGraph *graph,
           const char *xLabel = "not set",
           const char *yLabel = "not set",
           TString options = "pa")
{
    TCanvas *c = (TCanvas *)gROOT->GetListOfCanvases()->Last();
    c->cd(NPad);

    TString drawOpt = "";
    options.Append(" ");  // serve per "regolarizzare" la stringa
    options.Prepend(" "); // serve per "regolarizzare" la stringa

    // draw options ************************************************************
    graph->SetMarkerSize(0.7);
    graph->SetMarkerStyle(20);
    if (options.Contains(" pa "))
        drawOpt.Append("pa ");

    // layout options **********************************************************
    if (options.Contains(" logx "))
        c->GetPad(NPad)->SetLogx();
    if (options.Contains(" logy "))
        c->GetPad(NPad)->SetLogy();
    if (options.Contains(" gridx "))
        c->GetPad(NPad)->SetGridx();
    if (options.Contains(" gridy "))
        c->GetPad(NPad)->SetGridy();

    // axes ********************************************************************
    graph->GetXaxis()->SetTitle(xLabel);
    graph->GetYaxis()->SetTitle(yLabel);

    graph->DrawClone(drawOpt);

    // salvataggio su fileI
    if (options.Contains(" eps "))
        c->SaveAs(Form("fig/%s.eps", graph->GetName()));
    if (options.Contains(" svg "))
        c->SaveAs(Form("fig/%s.svg", graph->GetName()));
}

#endif