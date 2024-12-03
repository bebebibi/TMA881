#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <stddef.h>
#include <string.h>
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

void diffuse(int posX, int posY, float** nowMatrix, float** nextMatrix, float constant);
float calAvg(float** matrix, int rows, int cols);
float calAvgDiff(float** matrix, float avg, int rows, int cols);
float** mallocArray(int rows, int cols);
void outMatrix(float** matrix, int rows, int cols);

int main(int argc, char* argv[]) {
    cl_int error;

    cl_platform_id platform_id;
    cl_uint nmb_platforms;
    if (clGetPlatformIDs(1, &platform_id, &nmb_platforms) != CL_SUCCESS) {
        fprintf(stderr, "cannot get platform\n");
        return 1;
    }

    cl_device_id device_id;
    cl_uint nmb_devices;
    if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &nmb_devices) != CL_SUCCESS) {
        fprintf(stderr, "cannot get device\n");
        return 1;
    }

    cl_context context;
    cl_context_properties properties[] =
    {
      CL_CONTEXT_PLATFORM,
      (cl_context_properties)platform_id,
      0
    };
    context = clCreateContext(properties, 1, &device_id, NULL, NULL, &error);
    if (error != CL_SUCCESS) {
        fprintf(stderr, "cannot create context\n");
        return 1;
    }

    cl_command_queue command_queue;
    command_queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &error);
    if (error != CL_SUCCESS) {
        fprintf(stderr, "cannot create command queue\n");
        return 1;
    }

    char* opencl_program_src;
    {
        FILE* clfp = fopen("./1.cl", "r");
        if (clfp == NULL) {
            fprintf(stderr, "could not load cl source code\n");
            return 1;
        }
        fseek(clfp, 0, SEEK_END);
        int clfsz = ftell(clfp);
        fseek(clfp, 0, SEEK_SET);
        opencl_program_src = (char*)malloc((clfsz + 1) * sizeof(char));
        fread(opencl_program_src, sizeof(char), clfsz, clfp);
        opencl_program_src[clfsz] = 0;
        fclose(clfp);
    }

    cl_program program;
    size_t src_len = strlen(opencl_program_src);
    program = clCreateProgramWithSource(
        context, 1, (const char**)&opencl_program_src, (const size_t*)&src_len, &error);
    if (error != CL_SUCCESS) {
        fprintf(stderr, "cannot create program\n");
        return 1;
    }

    free(opencl_program_src);

    error = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (error != CL_SUCCESS) {
        fprintf(stderr, "cannot build program. log:\n");

        size_t log_size = 0;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        char* log = malloc(log_size * sizeof(char));
        if (log == NULL) {
            fprintf(stderr, "could not allocate memory\n");
            return 1;
        }

        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        fprintf(stderr, "%s\n", log);

        free(log);

        return 1;
    }

    cl_kernel kernel = clCreateKernel(program, "opencl", &error);
    if (error != CL_SUCCESS) {
        //fprintf(stderr, "cannot create kernel\n");
        //return 1;
    }

    int iterations = 1000;
    float constant = 0.01;

    const int rows = 100;
    const int cols = 100;



    //
    float** heatMatrix = mallocArray(rows + 2, cols + 2);
    float** nextMatrix = mallocArray(rows + 2, cols + 2);

    for (int i = 0; i < 75; i++) {
        int x = rand() % 99;
        int y = rand() % 99;
        heatMatrix[x][y] = rand()*9e13;
    }
    


    // iterations
    for (int it = 0; it < iterations; ++it) {
        // rows
        for (int i = 1; i < rows + 1; ++i) {
            // cols
            for (int j = 1; j < cols + 1; ++j) {
                diffuse(i, j, heatMatrix, nextMatrix, constant);
            }
        }
        // transfer
        heatMatrix = nextMatrix;
    }

    const int width_a = cols + 2;
    const int height_a = rows + 2;

    cl_mem input_buffer_a, input_buffer_b, output_buffer_c;
    input_buffer_a = clCreateBuffer(context, CL_MEM_READ_ONLY,
        width_a * height_a * sizeof(float), NULL, &error);
    if (error != CL_SUCCESS) {
        //fprintf(stderr, "cannot create buffer a\n");
        //return 1;
    }
    input_buffer_b = clCreateBuffer(context, CL_MEM_READ_ONLY,
        width_a * height_a * sizeof(float), NULL, &error);
    if (error != CL_SUCCESS) {
        //fprintf(stderr, "cannot create buffer b\n");
        //return 1;
    }
    output_buffer_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
        width_a * height_a * sizeof(float), NULL, &error);
    if (error != CL_SUCCESS) {
        //fprintf(stderr, "cannot create buffer c\n");
        //return 1;
    }

                
    if (clEnqueueWriteBuffer(command_queue,
        input_buffer_a, CL_TRUE, 0, width_a * height_a * sizeof(float), heatMatrix, 0, NULL, NULL)
        != CL_SUCCESS) {
        //fprintf(stderr, "cannot enqueue write of buffer a\n");
        //return 1;
    }
    if (clEnqueueWriteBuffer(command_queue,
        input_buffer_b, CL_TRUE, 0, width_a * height_a * sizeof(float), nextMatrix, 0, NULL, NULL)
        != CL_SUCCESS) {
        //fprintf(stderr, "cannot enqueue write of buffer b\n");
        //return 1;
    }

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buffer_a);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &input_buffer_b);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &output_buffer_c);
    clSetKernelArg(kernel, 3, sizeof(int), &width_a);
    clSetKernelArg(kernel, 4, sizeof(int), &width_a);

    const size_t global_sz[] = { width_a, height_a };
    if (clEnqueueNDRangeKernel(command_queue, kernel,
        2, NULL, (const size_t*)&global_sz, NULL, 0, NULL, NULL)
        != CL_SUCCESS) {
        //fprintf(stderr, "cannot enqueue kernel\n");
        //return 1;
    }

    float* c = malloc(width_a * height_a * sizeof(float));
    if (clEnqueueReadBuffer(command_queue,
        output_buffer_c, CL_TRUE, 0, width_a * height_a * sizeof(float), c, 0, NULL, NULL)
        != CL_SUCCESS) {
        //fprintf(stderr, "cannot enqueue read of buffer c\n");
        //return 1;
    }

    if (clFinish(command_queue) != CL_SUCCESS) {
        //fprintf(stderr, "cannot finish queue\n");
       // return 1;
    }

    clReleaseMemObject(input_buffer_a);
    clReleaseMemObject(input_buffer_b);
    clReleaseMemObject(output_buffer_c);



    // print matrix
    outMatrix(nextMatrix, rows, cols);

    // cal average temperature
    float matrixAvg = calAvg(nextMatrix, rows, cols);

    // temperature difference
    float matrixAvgDiff = calAvgDiff(nextMatrix, matrixAvg, rows, cols);

    clReleaseProgram(program);
    clReleaseKernel(kernel);

    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    return 0;
}

void diffuse(int posX, int posY, float** nowMatrix, float** nextMatrix, float constant)
{
    // h(i, j) = h(i, j) + c * ((h(i - 1, j) + h(i + 1, j) + h(i, j - 1) + h(i, j + 1)) / 4 - h(i,j))
    float tmpVal = nowMatrix[posX][posY];
    float surrounding = (nowMatrix[posX - 1][posY] +
        nowMatrix[posX + 1][posY] +
        nowMatrix[posX][posY - 1] +
        nowMatrix[posX][posY + 1]) / 4 - tmpVal;
    float nextValue = tmpVal + constant * surrounding;
    nextMatrix[posX][posY] = nextValue;
}

float calAvg(float** matrix, int rows, int cols) {
    long double sum = 0;
    for (int i = 1; i < rows + 1; ++i) {
        for (int j = 1; j < cols + 1; ++j) {
            sum += matrix[i][j];
        }
    }

    float matrixAvg = sum / rows / cols;
    printf("Avg of the matrix is %f\n" ,matrixAvg);
    return matrixAvg;
}

float calAvgDiff(float** matrix, float avg, int rows, int cols) {
    long double avgDiff = 0;
    for (int i = 1; i < rows + 1; ++i) {
        for (int j = 1; j < cols + 1; ++j) {
            avgDiff += abs(avg - matrix[i][j]);
        }
    }

    float matrixAvgDiff = avgDiff / rows / cols;
    printf( "Average absolute difference of each temperature to the average of all temperatures is  %f" , matrixAvgDiff);
    return matrixAvgDiff;
}

float** mallocArray(int rows, int cols) {
   
    float** arr = (float**)malloc(sizeof(float*) * rows);
    for (int i = 0; i < rows; i++) {
        arr[i] = (float*)malloc(sizeof(float*) * cols);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = 0;
        }
    }
    return arr;
}
void outMatrix(float** matrix, int rows, int cols) {
    for (int i = 1; i < rows + 1; ++i) {
        for (int j = 1; j < cols + 1; ++j) {
            printf("%f ",matrix[i][j]);
        }
        printf("\n");
    }
}
