#ifndef AIRHOCKEY_H_
#define AIRHOCKEY_H_

#ifdef __cplusplus
extern "C" {
#endif

void init(int width, int height);
void update();
void touch(int action, double x, double y);

#ifdef __cplusplus
}
#endif

#endif
