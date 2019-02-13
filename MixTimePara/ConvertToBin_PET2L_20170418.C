void ConvertToBin_PET2L_20170418()
{
  gROOT->Reset();
  char buf[100];
  char puf[100];
  const int fileN=10;
  const int part=1;
  TChain chain("Coincidences");   // name of the tree is the argument

   for(int j=0;j<100;j++){
   sprintf(buf,"iec_pet2l_offlcenter15cm_XYH%d.root",j+1); 
   chain.Add(buf);
   }
//
//Declaration of leaves types - TTree Coincidences
//  
   Int_t           RayleighCrystal1;
   Int_t           RayleighCrystal2;
   Int_t           RayleighPhantom1;
   Int_t           RayleighPhantom2;
   Char_t          RayleighVolName1[40];
   Char_t          RayleighVolName2[40];
   Float_t         axialPos;
   Char_t          comptVolName1[40];
   Char_t          comptVolName2[40];
   Int_t           compton1;
   Int_t           compton2;
   Int_t           rsectorID1;
   Int_t           moduleID1;
   Int_t           submoduleID1;
   Int_t           crystalID1;
   Int_t           layerID1;
   Int_t           rsectorID2;
   Int_t           moduleID2;
   Int_t           submoduleID2;
   Int_t           crystalID2;
   Int_t           layerID2;
   Int_t           comptonPhantom1;
   Int_t           comptonPhantom2;
   Float_t         energy1;
   Float_t         energy2;   
   Int_t           eventID1;
   Int_t           eventID2;
   Float_t         globalPosX1;
   Float_t         globalPosX2;
   Float_t         globalPosY1;
   Float_t         globalPosY2;      
   Float_t         globalPosZ1;
   Float_t         globalPosZ2;
   Float_t         rotationAngle;
   Int_t           runID;
   Float_t         sinogramS;
   Float_t         sinogramTheta;
   Int_t           sourceID1;
   Int_t           sourceID2;
   Float_t         sourcePosX1;
   Float_t         sourcePosX2;
   Float_t         sourcePosY1;
   Float_t         sourcePosY2;
   Float_t         sourcePosZ1;
   Float_t         sourcePosZ2;
   Double_t         time1;
   Double_t         time2;
   
   Float_t         zmin,zmax,z;
//   
//Set branch addresses - TTree Coincicences
//  
   chain.SetBranchAddress("RayleighCrystal1",&RayleighCrystal1);
   chain.SetBranchAddress("RayleighCrystal2",&RayleighCrystal2);
   chain.SetBranchAddress("RayleighPhantom1",&RayleighPhantom1);
   chain.SetBranchAddress("RayleighPhantom2",&RayleighPhantom2);
   chain.SetBranchAddress("RayleighVolName1",&RayleighVolName1);
   chain.SetBranchAddress("RayleighVolName2",&RayleighVolName2);
   chain.SetBranchAddress("comptVolName1",&comptVolName1);
   chain.SetBranchAddress("comptVolName2",&comptVolName2);
   chain.SetBranchAddress("comptonCrystal1",&compton1);
   chain.SetBranchAddress("comptonCrystal2",&compton2);
   chain.SetBranchAddress("comptonPhantom1",&comptonPhantom1);
   chain.SetBranchAddress("comptonPhantom2",&comptonPhantom2);
   chain.SetBranchAddress("energy1",&energy1);
   chain.SetBranchAddress("energy2",&energy2);   
   chain.SetBranchAddress("eventID1",&eventID1);
   chain.SetBranchAddress("eventID2",&eventID2);
   chain.SetBranchAddress("globalPosX1",&globalPosX1);
   chain.SetBranchAddress("globalPosX2",&globalPosX2);
   chain.SetBranchAddress("globalPosY1",&globalPosY1);
   chain.SetBranchAddress("globalPosY2",&globalPosY2);      
   chain.SetBranchAddress("globalPosZ1",&globalPosZ1);
   chain.SetBranchAddress("globalPosZ2",&globalPosZ2);
   chain.SetBranchAddress("rotationAngle",&rotationAngle);
   chain.SetBranchAddress("axialPos",&axialPos);
   chain.SetBranchAddress("runID",&runID);
   chain.SetBranchAddress("sinogramS",&sinogramS);
   chain.SetBranchAddress("sinogramTheta",&sinogramTheta);
   chain.SetBranchAddress("sourceID1",&sourceID1);
   chain.SetBranchAddress("sourceID2",&sourceID2);
   chain.SetBranchAddress("sourcePosX1",&sourcePosX1);
   chain.SetBranchAddress("sourcePosX2",&sourcePosX2);
   chain.SetBranchAddress("sourcePosY1",&sourcePosY1);
   chain.SetBranchAddress("sourcePosY2",&sourcePosY2);
   chain.SetBranchAddress("sourcePosZ1",&sourcePosZ1);
   chain.SetBranchAddress("sourcePosZ2",&sourcePosZ2);
   chain.SetBranchAddress("rsectorID1",&rsectorID1);
   chain.SetBranchAddress("moduleID1",&moduleID1);
   chain.SetBranchAddress("submoduleID1",&submoduleID1);
   chain.SetBranchAddress("crystalID1",&crystalID1);
   chain.SetBranchAddress("layerID1",&layerID1);
   chain.SetBranchAddress("rsectorID2",&rsectorID2);
   chain.SetBranchAddress("moduleID2",&moduleID2);
   chain.SetBranchAddress("submoduleID2",&submoduleID2);
   chain.SetBranchAddress("crystalID2",&crystalID2);
   chain.SetBranchAddress("layerID2",&layerID2);
   chain.SetBranchAddress("time1",&time1);
   chain.SetBranchAddress("time2",&time2);
   
  

/*
    FILE *fp_true = fopen("tof_true.bin","wb");
    FILE *fp_random = fopen("tof_random.bin","wb");
    FILE *fp_scatter = fopen("tof_scatter.bin","wb");
    FILE *fp_prompt = fopen("tof_prompt.bin","wb");
*/
    FILE *fp_true[fileN];
    FILE *fp_random[fileN]; 
    FILE *fp_scatter[fileN];
    FILE *fp_prompt[fileN]; 

    for(int ii=0;ii<fileN;ii++){
	sprintf(buf,"tof_true_rebin20_half_%d.bin",ii+1);
        fp_true[ii]=fopen(buf,"wb");
	sprintf(puf,"tof_random_rebin20_half_%d.bin",ii+1);
        fp_random[ii]=fopen(puf,"wb");
	sprintf(buf,"tof_scatter_rebin20_half_%d.bin",ii+1);
        fp_scatter[ii]=fopen(buf,"wb");
	sprintf(puf,"tof_prompt_rebin20_half_%d.bin",ii+1);
        fp_prompt[ii]=fopen(puf,"wb");
    }

	
   ULong64_t nentries = chain.GetEntries();
   	cout <<"all count is " <<nentries <<endl;
  
   
   ULong64_t nbytes = 0, nbytesdelay = 0, nrandom = 0, nscatter = 0, ntrue = 0, count = 0,d=1;
   ULong64_t coin_enegy1 = 0, coin_enegy2 = 0,coin_time_diff = 0 , coin_type=0;;
   ULong64_t coin_single_posi_axial1=0,coin_single_posi_axial2=0,coin_single_posi_trans1=0,coin_single_posi_trans2=0,coin_single_posi1=0,coin_single_posi2=0,coin_single_posi1_hpart=0;
   
//
// Loop for each event in the TTree Coincidences
//
  ULong64_t  flag=0;
  ULong64_t  count1=0, count2=0, count3=0;
   //for (ULong64_t i=0; i< 100000;i++)
   for (ULong64_t i=0; i<nentries;i++)
  {

     if (fmod((double)i,10000000.0) == 0.0) cout << ".";
    // if (fmod((double)i,1000000.0) == 0.0) { cout <<i/1000000 <<"M   "; }	 
     nbytes +=  chain.GetEntry(i);

	d=1L<<31;
	if(time2>time1){
        coin_enegy1=((ULong64_t(energy1*1000+0.5))&0x00000000000003ff)<<10;
        coin_enegy2=((ULong64_t(energy2*1000+0.5))&0x00000000000003ff);
	    coin_time_diff=((ULong64_t((time2-time1)*1000000000000.0/20.0+0.5))&0x00000000000000ff)<<20;
        coin_single_posi_trans1=(rsectorID1*16+(submoduleID1%2)*8+crystalID1%8)&0x00000000000003ff;
	    coin_single_posi_trans2=(rsectorID2*16+(submoduleID2%2)*8+crystalID2%8)&0x00000000000003ff;
	    coin_single_posi_axial1=( moduleID1*24+ULong64_t(submoduleID1/2.0)*8+ULong64_t(crystalID1/8.0))&0x000000000000003f;
        coin_single_posi_axial2=( moduleID2*24+ULong64_t(submoduleID2/2.0)*8+ULong64_t(crystalID2/8.0))&0x000000000000003f;
	}else{
        coin_enegy2=((ULong64_t(energy2*1000+0.5))&0x00000000000003ff)<<10;
        coin_enegy1=((ULong64_t(energy1*1000+0.5))&0x00000000000003ff);
	    coin_time_diff=((ULong64_t((time1-time2)*1000000000000.0/20.0+0.5))&0x00000000000000ff)<<20;
        coin_single_posi_trans2=(rsectorID2*16+(submoduleID2%2)*8+crystalID2%8)&0x00000000000003ff;
	    coin_single_posi_trans1=(rsectorID1*16+(submoduleID1%2)*8+crystalID1%8)&0x00000000000003ff;
	    coin_single_posi_axial2=( moduleID2*24+ULong64_t(submoduleID2/2.0)*8+ULong64_t(crystalID2/8.0))&0x000000000000003f;
        coin_single_posi_axial1=( moduleID1*24+ULong64_t(submoduleID1/2.0)*8+ULong64_t(crystalID1/8.0))&0x000000000000003f;
	}
		coin_type=1<<31;
		coin_single_posi1=(coin_single_posi_trans1<<6)+coin_single_posi_axial1;
        coin_single_posi2=(coin_single_posi_trans2<<6)+coin_single_posi_axial2;
        coin_single_posi1=coin_single_posi1<<48;
		coin_single_posi2=coin_single_posi2<<32;	
        

       flag= i/(nentries/fileN +1); 
		d+=coin_enegy1+coin_enegy2+coin_time_diff+coin_type+coin_single_posi1+coin_single_posi2;
        fwrite(&d,sizeof(d),1,fp_prompt[flag]);   


     if (eventID1 != eventID2) 
     { // Random coincidence
       ++nrandom;
        d=d&0xffffffff7fffffff;
        fwrite(&d,sizeof(d),1,fp_random[flag]);	 
     }

	else
   {  // True coincidence
       if (comptonPhantom1 == 0 && comptonPhantom2 == 0 &&
           RayleighPhantom1 == 0 && RayleighPhantom2 == 0) 
      {  // true unscattered coincidence
        ntrue++;
        if(time1>time2)count1++;
        else if(time1<time2)           count2++;
        else            count3++;
        fwrite(&d,sizeof(d),1,fp_true[flag]);	 
    }

	else
     { // true scattered coincidence
     nscatter++;
     fwrite(&d,sizeof(d),1,fp_scatter[flag]);	 
       }  
     }  
   }
   cout << endl << endl;
   cout << " There are " << ntrue << " true unscattered coincidences" << endl;
   cout << " There are " << nrandom << " random coincidences" << endl;
   cout << " There are " << nscatter << " scattered coincidences" << endl;
   cout << " There are " << nentries << " coincidences (true, scattered, and random)" << endl; 
  
   fclose(fp_true[flag]);
   fclose(fp_random[flag]);
   fclose(fp_scatter[flag]);
   fclose(fp_prompt[flag]);
   
   cout<<"counts of counts t1>t2-->"<<count1<<endl;
   cout<<"counts of counts t1<t2-->"<<count2<<endl;
   cout<<"counts of counts t1=t2-->"<<count3<<endl;

}	
