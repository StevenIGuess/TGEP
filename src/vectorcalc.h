#ifndef VECTORCALC_H
#define VECTORCALC_H
#include <math.h>

typedef struct vec2 {
    float x, y;
} vec2;

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct vec4 {
    float x, y, z, w;
} vec4;

typedef struct mat3{
    float x[3];
    float y[3];
    float z[3];
} mat3;
/*
1 1 1  x
2 2 2  y
3 3 3  z
*/
typedef struct mat4 {
    float x[4];
    float y[4];
    float z[4];
    float w[4];
} mat4;
/*
1 1 1 1 x
2 2 2 2 y 
3 3 3 3 z
4 4 4 4 w
*/

float radians(float degree) {
    return degree * (M_PI / 180.0f);
}

mat4 Matrix4(float x) {
    mat4 out;

    //generate standart identity matrix
    out.x[0] = x;
    out.x[1] = 0.0f;
    out.x[2] = 0.0f;
    out.x[3] = 0.0f;

    out.y[0] = 0.0f;
    out.y[1] = x;
    out.y[2] = 0.0f;
    out.y[3] = 0.0f;

    out.z[0] = 0.0f;
    out.z[1] = 0.0f;
    out.z[2] = x;
    out.z[3] = 0.0f;

    out.w[0] = 0.0f;
    out.w[1] = 0.0f;
    out.w[2] = 0.0f;
    out.w[3] = x;

    return out;
}

vec3 Vector3(float x, float y, float z) {
    vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    
    return vec;
}


//multiply vec3 by float
vec3 M_V3F(vec3 vec, float num) {
    vec3 out;

    out.x = vec.x * num;
    out.y = vec.y * num;
    out.z = vec.z * num;

    return out;
}

//multiply mat4 by mat4
mat4 M_M4M4(mat4 A, mat4 B) {
    mat4 out;

    for (int i = 0; i < 4; i++) {

        out.x[i] = A.x[0] * B.x[i]  +  A.x[1] * B.y[i]  +  A.x[2] * B.z[i]  +  A.x[3] * B.w[i];

        out.y[i] = A.y[0] * B.x[i]  +  A.y[1] * B.y[i]  +  A.y[2] * B.z[i]  +  A.y[3] * B.w[i];

        out.z[i] = A.z[0] * B.x[i]  +  A.z[1] * B.y[i]  +  A.z[2] * B.z[i]  +  A.z[3] * B.w[i];

        out.w[i] = A.w[0] * B.x[i]  +  A.w[1] * B.y[i]  +  A.w[2] * B.z[i]  +  A.w[3] * B.w[i];

    }

    return out;
}

//divide vec3 by float
vec3 D_V3F(vec3 vec, float num) { 
    vec3 out;

    out.x = vec.x / num;
    out.y = vec.y / num;
    out.z = vec.z / num;

    return out;
}

//subtract 2 vectors
vec3 S_V3V3(vec3 vec0, vec3 vec1) {
    vec3 out;

    out.x = vec0.x - vec1.x;
    out.y = vec0.y - vec1.y;
    out.z = vec0.z - vec1.z;
    
    return out;
}

void printV3(vec3 vec) {

    printf("\n%sx:%f\ny:%f\nz:%f\n", "VectorPrint::\n", vec.x, vec.y, vec.z);

}

void printM4(mat4 mat) {

    printf("\n%s", "Printing matrix 4 * 4 :: \n\n");

    for (int i = 0; i < 4; i++) {
        printf("%f ", mat.x[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", mat.y[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", mat.z[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", mat.w[i]);
    }
    printf("\n");
}

vec3 crossVec3(vec3 A, vec3 B) {
    vec3 out;

    out.x = A.y * B.z - A.z * B.y;
    out.y = A.z * B.x - A.x * B.z;
    out.z = A.x * B.y - A.y * B.x;

    return out;
}

vec3 normalizeV3(vec3 vec) {
    double length;
    vec3 normalVec;

    length = sqrt(pow(vec.x, 2.0) + pow(vec.y, 2.0) + pow(vec.z, 2.0));

    normalVec = D_V3F(vec, length);

    return normalVec;
}


mat4 lookAtMatrix(vec3 position, vec3 target, vec3 worldUp) {
    //1. Pos is known
    //2. Calculate cameraDirection
    vec3 zaxis = normalizeV3(S_V3V3(position, target));
    printf("ZAXIS::");
    printV3(zaxis);
    //3. Get positive right axis vector
    vec3 xaxis = normalizeV3(crossVec3(normalizeV3(worldUp), zaxis));
    printf("XAXIS::");
    printV3(xaxis);
    //4. Calculate camera up vec
    vec3 yaxis = crossVec3(zaxis, xaxis);
    printf("YAXIS::");
    printV3(yaxis);

    //Create translation and rotation matricies
    mat4 translation = Matrix4(1.0f);
    translation.x[3] = -position.x;
    translation.y[3] = -position.y;
    translation.z[3] = -position.z;
    printf("TransMat::\n");
    printM4(translation);

    mat4 rotation = Matrix4(1.0f);
    rotation.x[0] = xaxis.x;
    rotation.x[1] = xaxis.y;
    rotation.x[2] = xaxis.z;

    rotation.y[0] = yaxis.x;
    rotation.y[1] = yaxis.y;
    rotation.y[2] = yaxis.z;

    rotation.z[0] = zaxis.x;
    rotation.z[1] = zaxis.y;
    rotation.z[2] = zaxis.z;
    printf("RotMat::\n");
    printM4(rotation);


    return M_M4M4(rotation, translation);
}

#endif //VECTORCALC_H