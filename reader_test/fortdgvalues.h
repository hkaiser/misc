struct fortdg {
  int dgswe;
  int dg_to_cg;
  int modal_ic;
  int padapt; // only making sure this is zero.
  int pflag;
  int gflag;
  int dis_tol;
  int pl;
  int ph;
  int px;
  double slimit;
  int plimit;
  int k;
  double ks;
  int L;
  int nelem;
  int fluxtype;
  int rk_stage;
  int rk_order;
  int slopeflag;
  int weight;
  int sedflag;  // only making sure this is zero.
  //int porosity;
  //int sevdm;
  //int layers;
  // not doing sed_equations
  // not doing chemistry
  // not doing artificial diffusion
  
};
