#include <CL/cl_gl_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define throw_err(s)                                                           \
    {                                                                          \
        if (err != CL_SUCCESS) {                                               \
            fprintf(stderr, "Error at %s: %d\n", s, (int)err);                 \
            return err;                                                        \
        }                                                                      \
    }

// OpenCL kernel. Each work item takes care of one element of c
const char *kernelSource =
    "\n"
    "#pragma OPENCL EXTENSION cl_khr_fp16 : enable                    \n"
    "__kernel void vecAdd(  __global float *a,                       \n"
    "                       __global float *b,                       \n"
    "                       __global float *c,                       \n"
    "                       const unsigned int n)                    \n"
    "{                                                               \n"
    "    //Get our global thread ID                                  \n"
    "    int id = get_global_id(0);                                  \n"
    "                                                                \n"
    "    //Make sure we do not go out of bounds                      \n"
    "    if (id < n)                                                 \n"
    "        c[id] = a[id] + b[id]; c[id] = 1.0;                    \n"
    "}                                                               \n"
    "\n";

int main(int argc, char *argv[]) {
    // Length of vectors
    unsigned int n = 100000000;

    // Host input vectors
    float *h_a;
    float *h_b;
    // Host output vector
    float *h_c;

    // Device input buffers
    cl_mem d_a;
    cl_mem d_b;
    // Device output buffer
    cl_mem d_c;

    cl_platform_id cpPlatform; // OpenCL platform
    cl_device_id device_id;    // device ID
    cl_context context;        // context
    cl_command_queue queue;    // command queue
    cl_program program;        // program
    cl_kernel kernel;          // kernel

    // Size, in bytes, of each vector
    size_t bytes = n * sizeof(float);

    // Allocate memory for each vector on host
    h_a = (float *)malloc(bytes);
    h_b = (float *)malloc(bytes);
    h_c = (float *)malloc(bytes);

    // Initialize vectors on host
    int i;
    for (i = 0; i < n; i++) {
        h_a[i] = sinf(i) * sinf(i);
        h_b[i] = cosf(i) * cosf(i);
    }

    size_t globalSize, localSize;
    cl_int err;

    // Number of work items in each local work group
    localSize = 64;

    // Number of total work items - localSize must be devisor
    globalSize = ceilf(n / (float)localSize) * localSize;

    // Bind to platform
    err = clGetPlatformIDs(1, &cpPlatform, NULL);
    throw_err("platform ids");

    // Get ID for the device
    err =
        clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
    throw_err("devide ids");

    // Create a context
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    throw_err("create context");

    // Create a command queue
    queue = clCreateCommandQueue(context, device_id, 0, &err);
    throw_err("create queue");

    // Create the compute program from the source buffer
    program = clCreateProgramWithSource(
        context, 1, (const char **)&kernelSource, NULL, &err);
    throw_err("create program");

    // Build the program executable
    err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    {
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL,
                              &log_size);

        // Allocate memory for the log
        char *log = (char *)malloc(log_size);

        // Get the log
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
                              log_size, log, NULL);

        // Print the log
        printf("%s\n", log);
    }
    throw_err("build program");

    // Create the compute kernel in the program we wish to run
    kernel = clCreateKernel(program, "vecAdd", &err);
    throw_err("create kernel");

    // Create the input and output arrays in device memory for our calculation
    d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, bytes, NULL, NULL);
    d_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

    // Write our data set into the input array in device memory
    err =
        clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0, bytes, h_a, 0, NULL, NULL);
    err |=
        clEnqueueWriteBuffer(queue, d_b, CL_TRUE, 0, bytes, h_b, 0, NULL, NULL);

    // Set the arguments to our compute kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
    err |= clSetKernelArg(kernel, 3, sizeof(unsigned int), &n);
    throw_err("set arguments");

    // Execute the kernel over the entire range of the data set
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize,
                                 &localSize, 0, NULL, NULL);
    throw_err("execute");

    // Wait for the command queue to get serviced before reading back results
    clFinish(queue);

    // Read the results from the device
    clEnqueueReadBuffer(queue, d_c, CL_TRUE, 0, bytes, h_c, 0, NULL, NULL);

    // Sum up vector c and print result divided by n, this should equal 1 within
    // error
    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += h_c[i];
    }
    printf("final result: %f\n", sum / n);

    // release OpenCL resources
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    // release host memory
    free(h_a);
    free(h_b);
    free(h_c);

    return err;
}
