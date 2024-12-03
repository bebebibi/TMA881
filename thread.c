#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>
#include <complex.h> 

int line;
int nthrds;
int expn;



// char **color_set;
// char *


//static inline
void
newton(
  double complex pixel,
  unsigned short *attractor, 
  unsigned short *convergence
  )
{
  int conv;
  int attr;



  switch ( expn ) {
  case 1:
    double true_root_real[]={1.};
    double true_root_ima[]={0.};
    double real_value;
    double ima_value;
    


    for (  conv = 0, attr = 0; ; ++conv ) {
      real_value=creal(pixel);
      ima_value=cimag(pixel);
      if ( (real_value*real_value+ima_value*ima_value)<0.000001  ) {
        attr = 0;
        break;
        }
      if ( real_value>10000000000|| real_value<-10000000000||ima_value>10000000000||ima_value<-10000000000) {
        attr = 0;
        break;
        }
     // for (int ix=0 ;ix <1;++ix )
     // {
          if (( (real_value-true_root_real[0])*(real_value-true_root_real[0])+(ima_value-true_root_ima[0])*(ima_value-true_root_ima[0]))<0.000001 ) {
          attr = 1;
          *attractor=attr;
          break;
      //}

      } 
      if ( attr != 0 )
      {
        break;
      }

      pixel=CMPLX(1, 0);

    }

    if (conv>50){
      conv=50;
    }

    *convergence= conv;
    break;


  case 2:
    double true_root_real2[]={ -1.,1.};
    double true_root_ima2[]={0.,0.};

    for (conv = 0, attr = 0; ; ++conv ) {
        if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001  ) {
        attr = 0;
        break;
        }
      if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
        attr = 0;
        break;
        }
      for (int ix=0;ix <expn;++ix )
      {
          if ( ((creal(pixel)-true_root_real2[ix])*(creal(pixel)-true_root_real2[ix])+(cimag(pixel)-true_root_ima2[ix])*(cimag(pixel)-true_root_ima2[ix]))<0.000001 ) {
          attr = ix+1;
          *attractor=attr;
          break;
      }

      } 
      if ( attr != 0 )
      {
        break;
      }

      pixel=pixel-(pixel*pixel-1)/(2*pixel);

      }

    if (conv>50){
      conv=50;
    }

    *convergence= conv;

    break;
  case 3:
    double true_root_real3[]={-0.5,-0.5,1.};
    double true_root_ima3[]={0.8660254,-0.8660254,0.};


    for ( conv = 0, attr = 0; ; ++conv ) {
      if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001  ) {
        attr = 0;
        break;
        }
      if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
        attr = 0;
        break;
        }
      for (int ix=0; ix <expn;++ix )
      {
        if ( ((creal(pixel)-true_root_real3[ix])*(creal(pixel)-true_root_real3[ix])+(cimag(pixel)-true_root_ima3[ix])*(cimag(pixel)-true_root_ima3[ix]))<0.000001 ) {
        attr = ix+1;
        *attractor=attr;
        break;
      }

      } 
      if ( attr != 0 )
      {
        break;
      }
      double complex pixel2=pixel*pixel;

      pixel=pixel-(pixel*pixel2-1)/(3*pixel2);


  }
  


    if (conv>50){
      conv=50;
    }
    *convergence= conv;
    break;

  case 4:
    double true_root_real4[]={0.,-1.,0.,1.};
    double true_root_ima4[]={ 1.,  0., -1., 0.};
  // insert further cases
    for ( conv = 0, attr = 0; ; ++conv ) {
      if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001  ) {
        attr = 0;
        break;
        }
      if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
        attr = 0;
        break;
        }
      for (int ix=0; ix <expn;++ix )
      {
          if ( ((creal(pixel)-true_root_real4[ix])*(creal(pixel)-true_root_real4[ix])+(cimag(pixel)-true_root_ima4[ix])*(cimag(pixel)-true_root_ima4[ix]))<0.000001 ) {
          attr = ix+1;
          *attractor=attr;
          break;
        }
      } 
      if ( attr != 0 )
      {
        break;
      }
      double complex pixel2=pixel*pixel;

      pixel=pixel-(pixel2*pixel2-1)/(4*pixel*pixel2);

    }

    if (conv>50){
    conv=50;
    }
    *convergence= conv;
    break;

  case 5:

    double true_root_real5[]={0.30901699,-0.80901699,-0.80901699,0.30901699,1.};
    double true_root_ima5[]={0.95105652, 0.58778525, -0.58778525, -0.95105652, 0.};

  // insert further cases
    for ( conv = 0, attr = 0; ; ++conv ) {
    if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001 ) {
      attr = 0;
      break;
      }
    if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
      attr = 0;
      break;
      }
    for (int ix=0; ix < expn;++ix )
    {
        if ( ((creal(pixel)-true_root_real5[ix])*(creal(pixel)-true_root_real5[ix])+(cimag(pixel)-true_root_ima5[ix])*(cimag(pixel)-true_root_ima5[ix]))<0.000001 ) {
        attr = ix+1;
        *attractor=attr;
        break;
      }
    } 
    if ( attr != 0 )
    {
      break;
    }
    double complex pixel2=pixel*pixel;
    double complex pixel4=pixel2*pixel2;
    pixel=pixel-(pixel*pixel4-1)/(5*pixel4);

  }

    if (conv>50){
    conv=50;
    }
    *convergence= conv;
    //printf("product %.2f + %2fi\n ",creal(pixel),cimag(pixel));
    break;

    case 6:

    double true_root_real6[]={0.5,-0.5,-1.0,-0.5,0.5,1.};
    double true_root_ima6[]={0.8660254, 0.8660254, 0., -0.8660254,-0.8660254,0.};

  // insert further cases
    for ( conv = 0, attr = 0; ; ++conv ) {
    if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001 ) {
      attr = 0;
      break;
      }
    if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
      attr = 0;
      break;
      }
    for (int ix=0; ix < expn;++ix )
    {
        if ( ((creal(pixel)-true_root_real6[ix])*(creal(pixel)-true_root_real6[ix])+(cimag(pixel)-true_root_ima6[ix])*(cimag(pixel)-true_root_ima6[ix]))<0.000001 ) {
        attr = ix+1;
        *attractor=attr;
        break;
      }
    } 
    if ( attr != 0 )
    {
      break;
    }
    double complex pixel2=pixel*pixel;
    double complex pixel4=pixel2*pixel2;
    pixel=pixel-(pixel2*pixel4-1)/(6*pixel4*pixel);

  }

    if (conv>50){
    conv=50;
    }
    *convergence= conv;
    //printf("product %.2f + %2fi\n ",creal(pixel),cimag(pixel));
    break;

    case 7:

    double true_root_real7[]={0.6234898,-0.22252093,-0.90096887,-0.90096887,-0.22252093,0.6234898,1.};
    double true_root_ima7[]={0.78183148, 0.97492791, 0.43388374, -0.43388374, -0.97492791, -0.78183148,0.};

  // insert further cases
    for ( conv = 0, attr = 0; ; ++conv ) {
    if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001 ) {
      attr = 0;
      break;
      }
    if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
      attr = 0;
      break;
      }
    for (int ix=0; ix < expn;++ix )
    {
        if ( ((creal(pixel)-true_root_real7[ix])*(creal(pixel)-true_root_real7[ix])+(cimag(pixel)-true_root_ima7[ix])*(cimag(pixel)-true_root_ima7[ix]))<0.000001 ) {
        attr = ix+1;
        *attractor=attr;
        break;
      }
    } 
    if ( attr != 0 )
    {
      break;
    }
    double complex pixel2=pixel*pixel;
    double complex pixel4=pixel2*pixel2;
    double complex pixel6=pixel4*pixel2;

    pixel=pixel-(pixel6*pixel-1)/(7*pixel6);

  }

    if (conv>50){
    conv=50;
    }
    *convergence= conv;
    //printf("product %.2f + %2fi\n ",creal(pixel),cimag(pixel));
    break;    


    case 8:

    double true_root_real8[]={ 0.70710678, 0.,-0.70710678,-1.0, -0.70710678, 0.,  0.70710678,1.};
    double true_root_ima8[]={0.70710678, 1., 0.70710678, 0., -0.70710678, -1., -0.70710678,0.};

  // insert further cases
    for ( conv = 0, attr = 0; ; ++conv ) {
    if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001 ) {
      attr = 0;
      break;
      }
    if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
      attr = 0;
      break;
      }
    for (int ix=0; ix < expn;++ix )
    {
        if ( ((creal(pixel)-true_root_real8[ix])*(creal(pixel)-true_root_real8[ix])+(cimag(pixel)-true_root_ima8[ix])*(cimag(pixel)-true_root_ima8[ix]))<0.000001 ) {
        attr = ix+1;
        *attractor=attr;
        break;
      }
    } 
    if ( attr != 0 )
    {
      break;
    }
    double complex pixel2=pixel*pixel;
    double complex pixel4=pixel2*pixel2;
    double complex pixel8=pixel4*pixel4;

    pixel=pixel-(pixel8-1)/(8*pixel4*pixel2*pixel);

  }

    if (conv>50){
    conv=50;
    }
    *convergence= conv;
    //printf("product %.2f + %2fi\n ",creal(pixel),cimag(pixel));
    break;    

    case 9:

    double true_root_real9[]={ 0.76604444, 0.17364818,-0.5, -0.93969262, -0.93969262,-0.5,  0.17364818, 0.76604444,1.};
    double true_root_ima9[]={0.64278761, 0.98480775, 0.8660254, 0.34202014, -0.34202014, -0.8660254, -0.98480775, -0.64278761,0.};

  // insert further cases
    for ( conv = 0, attr = 0; ; ++conv ) {
    if ( (creal(pixel)*creal(pixel)+cimag(pixel)*cimag(pixel))<0.000001 ) {
      attr = 0;
      break;
      }
    if ( creal(pixel)>10000000000|| creal(pixel)<-10000000000||cimag(pixel)>10000000000||cimag(pixel)<-10000000000) {
      attr = 0;
      break;
      }
    for (int ix=0; ix < expn;++ix )
    {
        if ( ((creal(pixel)-true_root_real9[ix])*(creal(pixel)-true_root_real9[ix])+(cimag(pixel)-true_root_ima9[ix])*(cimag(pixel)-true_root_ima9[ix]))<0.000001 ) {
        attr = ix+1;
        *attractor=attr;
        break;
      }
    } 
    if ( attr != 0 )
    {
      break;
    }
    double complex pixel2=pixel*pixel;
    double complex pixel4=pixel2*pixel2;
    double complex pixel8=pixel4*pixel4;

    pixel=pixel-(pixel8*pixel-1)/(9*pixel8);

  }

    if (conv>50){
    conv=50;
    }
    *convergence= conv;
    //printf("product %.2f + %2fi\n ",creal(pixel),cimag(pixel));
    break;    


  default:
    fprintf(stderr, "unexpected degree\n");
    exit(1);
}


}


static inline
unsigned short
convert_index(unsigned short count)
{
  unsigned short index;
  if (count<50){

    index = count/5;

  }else{
    index= 9;
  }
  return index;
}


typedef struct {
  int val;
  char pad[60]; // cacheline - sizeof(int)
} int_padded;

typedef struct {
  unsigned short **attractors;
  unsigned short **convergences;
  int ib;
  int istep;
  int sz;
  int tx;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_t;

typedef struct {
  unsigned short **attractors;
  unsigned short **convergences;
  int sz;
  int nthrds;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_check_t;


int
main_thrd(
    void *args
    )
{
  const thrd_info_t *thrd_info = (thrd_info_t*) args;
  unsigned short **attractors = thrd_info->attractors;
  unsigned short **convergences = thrd_info->convergences;
  const int ib = thrd_info->ib;
  const int istep = thrd_info->istep;
  const int sz = thrd_info->sz;
  const int tx = thrd_info->tx;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;
  

  for ( size_t ix = ib; ix < sz; ix += istep ) {

    // We allocate the rows of the result before computing, and free them in another thread.
    unsigned short *attractor = ( unsigned short*) malloc(sz*sizeof( unsigned short));

    unsigned short *convergence = (unsigned short*) malloc(sz*sizeof(unsigned short));

    double ima_part= 2. - (4.*ix/sz);



//computing


    for (int jx=0; jx < sz; jx++)
    {
      double real_part= -2.+ (4.*jx/sz);
      double complex pixel= CMPLX(real_part, ima_part);
      //printf("product %.2f + %2fi\n ",creal(pixel),cimag(pixel));
      newton(pixel, &attractor[jx], &convergence[jx]);
    }

    
  //
    

    mtx_lock(mtx);

    attractors[ix] = attractor;
    convergences[ix]= convergence;
    status[tx].val = ix + istep;
    mtx_unlock(mtx);
    cnd_signal(cnd);

    //thrd_sleep(&(struct timespec){.tv_sec=0, .tv_nsec=1000}, NULL);
  }

  return 0;
}


int
main_thrd_check(
    void *args
    )
{
  const thrd_info_check_t *thrd_info = (thrd_info_check_t*) args;
  unsigned short **attractors = thrd_info->attractors;
  unsigned short **convergences = thrd_info->convergences; 
  const int sz = thrd_info->sz;
  const int nthrds = thrd_info->nthrds;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  char color_set[10][9];
  char color_set2[10][9];
  memcpy(color_set[0],&"02 02 02 ",9);
  memcpy(color_set[1],&"05 05 05 ",9);
  memcpy(color_set[2],&"10 10 10 ",9);
  memcpy(color_set[3],&"15 15 15 ",9);
  memcpy(color_set[4],&"20 20 20 ",9);
  memcpy(color_set[5],&"25 25 25 ",9);
  memcpy(color_set[6],&"30 30 30 ",9);
  memcpy(color_set[7],&"35 35 35 ",9);
  memcpy(color_set[8],&"40 40 40 ",9);
  memcpy(color_set[9],&"50 50 50 ",9);


  memcpy(color_set2[0],&"01 02 03 ",9);
  memcpy(color_set2[1],&"05 02 01 ",9);
  memcpy(color_set2[2],&"01 05 03 ",9);
  memcpy(color_set2[3],&"02 03 08 ",9);
  memcpy(color_set2[4],&"05 07 01 ",9);
  memcpy(color_set2[5],&"08 01 08 ",9);
  memcpy(color_set2[6],&"03 09 02 ",9);
  memcpy(color_set2[7],&"05 05 03 ",9);
  memcpy(color_set2[8],&"02 03 09 ",9);
  memcpy(color_set2[9],&"07 02 08 ",9);




  // char **color_set[10];
  // color_set[0] = "02 02 02";


  for ( int ix = 0, ibnd; ix < sz; ) {


    for ( mtx_lock(mtx); ; ) {

      ibnd = sz;
      for ( int tx = 0; tx < nthrds; ++tx )
        if ( ibnd > status[tx].val )
          ibnd = status[tx].val;

      if ( ibnd <= ix )

        cnd_wait(cnd,mtx);
      else {
        mtx_unlock(mtx);
        break;
      }


    }

    //fprintf(stderr, "checking until %i\n", ibnd);

    FILE *file=fopen("newton_attractor_xd.ppm","a");

    FILE *file2=fopen("newton_convergence_xd.ppm","a");

    if(file==NULL ){
    printf("error opening file \n");
    return -1;
    }


    for ( ; ix < ibnd; ++ix ) 
    { 


      //printf("%d\n", attractors[ix]);

      char *pixel_row_attractor=  (char*) malloc((9*sz)*sizeof(char));

      char *pixel_row_convergence=  (char*) malloc((9*sz)*sizeof(char));
      
      char new_line='\n';

     

      for (int jx = 0; jx<sz ; jx++)
      { 
        unsigned short index=attractors[ix][jx];
        //printf("%d \n",attractors[ix][jx]);
        memcpy(&pixel_row_attractor[9*jx],color_set2[index],9);
      }
      
      memcpy(&pixel_row_attractor[9*sz-1],&new_line,1);



      for (int jx = 0; jx<sz ; jx++)
      {
        unsigned short index = convert_index(convergences[ix][jx]);
        memcpy(&pixel_row_convergence[9*jx],color_set[index],9);
      }

      memcpy(&pixel_row_convergence[9*sz-1],&new_line,1);


      fwrite((void*)pixel_row_attractor, sizeof(char), sz*9, file); 

      fwrite((void*)pixel_row_convergence, sizeof(char), sz*9, file2); 


      free(attractors[ix]);
      free(convergences[ix]);
      //printf("%d \n", *convergences[ix]);
      }

      fclose(file);
      fclose(file2);
    }

    
    return 0;
  }

  




int main(int argc, char* argv[])
{
    int opt;
    char *l, *t;
    while ((opt = getopt(argc, argv, "l:t::")) != -1) {
        switch (opt) {
        case 'l':
            l = optarg;
            break;
        case 't':
            t = optarg;
            break;
        }
    }
    line = strtol(l,NULL,10);//number of rows and columns

    nthrds = strtol(t,NULL,10);//number of threads
    expn = strtol(argv[3],NULL,10);//exponent of our function

    //printf("line: %i, thread: %i, exponent: %i\n",line,nthrds,expn);//check of command line, can be deleted

    //////////////////////////////////////
    //


//  




    unsigned short **attractors = (unsigned short**) malloc(line*sizeof(unsigned short*));
    

    unsigned short **convergences = (unsigned short**) malloc(line*sizeof(unsigned short*));


    FILE *file=fopen("newton_attractor_xd.ppm","w");

    if(file==NULL ){
        printf("error opening file \n");
        return -1;
        } 
    char line_string[10];
    sprintf(line_string,"%d",line);

    fwrite("P3", sizeof(char), 2, file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(line_string, sizeof(char), strlen(line_string), file);
    fwrite(" ", sizeof(char), 1, file);
    fwrite(line_string, sizeof(char), strlen(line_string), file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite("10", sizeof(char), 2, file);
    fwrite("\n", sizeof(char), 1, file); 

    fclose(file);




    FILE *file2=fopen("newton_convergence_xd.ppm","w");

    if(file==NULL ){
        printf("error opening file \n");
        return -1;
        } 

    fwrite("P3", sizeof(char), 2, file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(line_string, sizeof(char), strlen(line_string), file2);
    fwrite(" ", sizeof(char), 1, file);
    fwrite(line_string, sizeof(char), strlen(line_string), file2);
    fwrite("\n", sizeof(char), 1, file);
    fwrite("51", sizeof(char), 3, file);
    fwrite("\n", sizeof(char), 1, file); 

    fclose(file2);



//
    mtx_t mtx;
    mtx_init(&mtx, mtx_plain);

    cnd_t cnd;
    cnd_init(&cnd);

    thrd_t thrds[nthrds];
    thrd_info_t thrds_info[nthrds];

    thrd_t thrd_check;
    thrd_info_check_t thrd_info_check;

    int_padded status[nthrds];


  for ( int tx = 0; tx < nthrds; ++tx ) {
    thrds_info[tx].attractors = attractors;
    thrds_info[tx].convergences = convergences;
    thrds_info[tx].ib = tx;
    thrds_info[tx].istep = nthrds;
    thrds_info[tx].sz = line;
    thrds_info[tx].tx = tx;
    thrds_info[tx].mtx = &mtx;
    thrds_info[tx].cnd = &cnd;
    thrds_info[tx].status = status;
    status[tx].val = -1;

    int r = thrd_create(thrds+tx, main_thrd, (void*) (thrds_info+tx));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
    //thrd_detach(thrds[tx]);
  }

  {
    thrd_info_check.attractors = attractors;
    thrd_info_check.convergences = convergences;
    thrd_info_check.sz = line;
    thrd_info_check.nthrds = nthrds;
    thrd_info_check.mtx = &mtx;
    thrd_info_check.cnd = &cnd;
    thrd_info_check.status = status;

    int r = thrd_create(&thrd_check, main_thrd_check, (void*) (&thrd_info_check));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
  }

  {
    int r;
    thrd_join(thrd_check, &r);
  }


    free(attractors);
    free(convergences);


    mtx_destroy(&mtx);
    cnd_destroy(&cnd);

    return 0;
}




/*
int compute(void *args){
    const thrd_info_t *thrd_info=(thrd_info_t*)args;//obtain data from main
    int lb=thrd_info->lb;
    int ub=thrd_info->ub;
    int tx=thrd_info->tx;

    for(int ix=lb;ix<ub;++ix){
        printf("%d\n",ix);
    }
    return 0;
}

int writetofile(void *args){
    const thrd_info_write_t *thrd_info=(thrd_info_write_t*)args;//obtain data from main

    return 0;
} */


