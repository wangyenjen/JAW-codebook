#include <unistd.h>

// input optimize
inline int my_getchar() {
	const int N = 1<<20;
	static char buf[N];
	static char *p = buf , *end = buf;
	if(p == end) {
		if((end = buf + fread(buf , 1 , N , stdin)) == buf) return EOF;
		p = buf;
	}
	return *p++;
}

inline int readint(int &x) {
  static char c , neg;
  while((c = my_getchar()) < '-') {
    if(c == EOF) return 0;
  }
  neg = (c == '-') ? -1 : 1;
  x = (neg == 1) ? c - '0' : 0;
  while((c = my_getchar()) >= '0') x = (x << 3) + (x << 1) + (c - '0');
  x *= neg;
  return 1;
}

// output optimize
const int kBufSize = 524288;
char inbuf[kBufSize];
char buf_[kBufSize]; size_t size_;
inline void Flush_() { write(1, buf_, size_); size_ = 0; }
inline void CheckFlush_(size_t sz) { if (sz + size_ > kBufSize) Flush_(); }

inline void PutInt(int a) {
	static char tmp[22] = "01234567890123456789\n";
	CheckFlush_(10);
	int tail = 20;
	if (!a) {
		tmp[--tail] = '0';
	} else {
		for (; a; a /= 10) tmp[--tail] = (a % 10) ^ '0';
	}
	memcpy(buf_ + size_, tmp + tail, 21 - tail);
	size_ += 21 - tail;
}


