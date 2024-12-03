#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

//read the binary file and allocate heap memory for cells blocks.
static inline
float*
load_new_cells(
    size_t cells_size,
    size_t remaining_cells,
    size_t  cells_total
){
    if (cells_size >= remaining_cells){
        cells_size = remaining_cells;
    }

    size_t file_pointer_position = cells_total*24-remaining_cells*24;



    FILE *file=fopen("cells","r");



    fseek(file, file_pointer_position ,SEEK_SET);

    char *matrix = (char*) malloc(sizeof(char) *cells_size*24);

    fread(matrix,sizeof(char),cells_size*24,file);

    fclose(file);


    float *float_matrix = (float*) malloc(sizeof(float) * cells_size*3);

    for(size_t ix=0; ix < cells_size*3 ; ix++){
        float_matrix[ix] = atof(&matrix[ix*8]);

    }//char to float

    free(matrix); //free char heap memory inside function


   return float_matrix;
}




//calculate cell distances and counting for two memory blocks
static inline
void
calculate_distance_block(
    float *float_matrix_ref,
    float *float_matrix_read,
    size_t *count,
    size_t cells_size,
    size_t resource,
    size_t remaining_cells_ref,
    size_t remaining_cells_read
    )
{
    size_t ix;
    size_t jx;
    size_t index;
    float d;

    size_t cells_size_ref= cells_size;
    size_t cells_size_read= cells_size;

    if(cells_size >= remaining_cells_ref){
        cells_size_ref=remaining_cells_ref;
    }

    if(cells_size  >= remaining_cells_read){
        cells_size_read=remaining_cells_read;
    }

    if(resource==1){
//calculate cell distances for the same memory blocks
        #pragma omp parallel for default(none) private(d,index,ix,jx) shared(float_matrix_ref,float_matrix_read,cells_size_ref,cells_size_read) reduction(+:count[:3465])
        for (ix = 0; ix < cells_size_ref-1; ix++){
		    for (jx = ix+1; jx < cells_size_read; jx++){
				float d =sqrtf((float_matrix_ref[3*ix] - float_matrix_read[3*jx])*(float_matrix_ref[3*ix] - float_matrix_read[3*jx]) + (float_matrix_ref[3*ix+1] - float_matrix_read[3*jx+1])*(float_matrix_ref[3*ix+1]-float_matrix_read[3*jx+1]) + (float_matrix_ref[3*ix+2] - float_matrix_read[3*jx+2])*(float_matrix_ref[3*ix+2]-float_matrix_read[3*jx+2]));
			    size_t index= (size_t)(d * 100.f + 0.5f);
                
                count[index]+=1;
            }
        }

    }

    if(resource==0){
//calculate cell distances for different memory blocks
    #pragma omp parallel for default(none) private(d,index,ix,jx) shared(float_matrix_ref,float_matrix_read,resource,cells_size_ref,cells_size_read) reduction(+:count[:3465])
    for (ix = 0; ix < cells_size_ref; ix++){

        for (jx = 0; jx < cells_size_read; jx++){
                float d =sqrtf((float_matrix_ref[3*ix] - float_matrix_read[3*jx])*(float_matrix_ref[3*ix] - float_matrix_read[3*jx]) + (float_matrix_ref[3*ix+1] - float_matrix_read[3*jx+1])*(float_matrix_ref[3*ix+1]-float_matrix_read[3*jx+1]) + (float_matrix_ref[3*ix+2] - float_matrix_read[3*jx+2])*(float_matrix_ref[3*ix+2]-float_matrix_read[3*jx+2]));
            size_t index= (size_t)(d * 100.f + 0.5f);
            count[index]+=1;

        }
    }

}






}


int main(int argc, char *argv[]){
// command line
    size_t length_thread=0;
    while(argv[1][length_thread+2] != '\0'){
	length_thread++;
    }
    size_t t;
    if(length_thread==1){
        t = argv[1][2]-'0';
    }

    if(length_thread==2){
        t = 10*(argv[1][2] - '0') + (argv[1][3] -'0');
    }

    omp_set_num_threads(t);


//calculate the total cells
    FILE *file=fopen("cells","r");

    if(file == NULL){
        printf("error opening file \n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    size_t length=ftell(file);

    rewind(file);

    fclose(file);

    size_t cells_total=length/24; //number of cells
    size_t cells_size=5000; // load 5000 cells each time

    size_t count[3465];
    for (size_t ix = 0; ix <3465; ++ix){
        count[ix] = 0 ;
    }
    

    size_t remaining_cells_ref = cells_total;
    size_t remaining_cells_read = cells_total;

    size_t resource;


    while(remaining_cells_ref >0){

        remaining_cells_read = remaining_cells_ref;

        
        float *float_matrix_ref = load_new_cells(cells_size, remaining_cells_ref, cells_total);

        resource = 1;

        while(remaining_cells_read > 0){
            
            float *float_matrix_read = load_new_cells(cells_size, remaining_cells_read, cells_total);
            


            calculate_distance_block(float_matrix_ref, float_matrix_read, count, cells_size, resource,remaining_cells_ref,remaining_cells_read);

            remaining_cells_read -= cells_size;

            resource = 0;

            free(float_matrix_read);

        }

        remaining_cells_ref -= cells_size;

        free(float_matrix_ref);


    }


//printing the frequency of cell distances
    for (size_t ix = 0; ix<3465;++ix){
    //    if(count[ix]>0){
        printf("%05.2f %d\n",(float)ix*0.01f,count[ix]);
    }


    

}
