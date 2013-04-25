#ifndef AIRHOCKEY_H_
#define AIRHOCKEY_H_

#ifdef __cplusplus
extern "C" {
#endif

void init();
void update();
void touch(int action, double x, double y);

#ifdef __cplusplus
}
#endif

#endif
