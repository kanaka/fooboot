#include <stdint.h>
#include <math.h>

double fabs(double x) {
    return x < 0 ? -x : x;
}

double fmin(double x, double y) {
    // TODO: take into account NAN
    return x < y ? x : y;
}

double fmax(double x, double y) {
    // TODO: take into account NAN
    return x > y ? x : y;
}

double ceil(double x) {
    // TODO: implement
    return x;
}


uint32_t __popcountdi2(double a) {
    // TODO: implement
    (void)a;
    return 0;
}

uint32_t __popcountsi2(int32_t a) {
    // TODO: implement
    (void)a;
    return 0;
}

int32_t __ctzsi2(int32_t a) {
    // TODO: implement
    (void)a;
    return 0;
}



int64_t __divdi3(int64_t a, int64_t b) {
    // TODO: implement
    (void)a; (void)b;
    return 0;

}
int64_t __udivdi3(int64_t a, int64_t b) {
    // TODO: implement
    (void)a; (void)b;
    return 0;

}

int64_t __moddi3(int64_t a, int64_t b) {
    // TODO: implement
    (void)a; (void)b;
    return 0;

}
int64_t __umoddi3(int64_t a, int64_t b) {
    // TODO: implement
    (void)a; (void)b;
    return 0;

}


uint32_t __ctzdi2(int64_t a) {
    // TODO: implement
    (void)a;
    return 0;
}

int signbit(double x) {
    // TODO: implement
    (void)x;
    return 0;
}

double floor(double x) {
    // TODO: implement
    (void)x;
    return 0.0;
}

double trunc(double x) {
    // TODO: implement
    (void)x;
    return 0.0;
}

double rint(double x) {
    // TODO: implement
    (void)x;
    return 0.0;
}

double sqrt(double x) {
    // TODO: implement
    (void)x;
    return 0.0;
}
