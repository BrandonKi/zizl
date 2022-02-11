#ifndef ZIZL_SPAN_H
#define ZIZL_SPAN_H

#include <string_view>

class Span {
  public:
    char* start;
    char* end;

    inline char operator [](size_t index) {
        return start[index];
    }

    operator std::string_view() const {
        return std::string_view(start, end - start + 1);
    }
};

inline bool operator ==(Span span1, Span span2) {
    if(span1.end - span1.start != span2.end - span2.start)
        return false;

    for(int i = 0; i < span1.end - span1.start; ++i)
        if(span1[i] != span2[i])
            return false;
    return true;
}


#endif // ZIZL_SPAN_H
