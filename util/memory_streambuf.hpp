#pragma once

#include <streambuf>
#include <vector>

template<typename CharT, typename TraitsT = std::char_traits<CharT>>
class memory_streambuf : public std::basic_streambuf<CharT, TraitsT> {
    using base_sbuf = std::basic_streambuf<CharT, TraitsT>;
public:
    memory_streambuf(CharT* ptr, size_t len) : ptr(ptr), len(len) {
        this->setg(ptr, ptr, ptr + len);
        this->setp(ptr, ptr + len);
    }
    memory_streambuf(std::vector<CharT>& v) : memory_streambuf(v.data(), v.size()) {}

protected:
    base_sbuf::int_type overflow( base_sbuf::int_type ch = TraitsT::eof() ) {
        printf("bug: overran streambuf!\n");
        return -1;
    }

    base_sbuf::pos_type seekoff( base_sbuf::off_type off, std::ios_base::seekdir dir,
        std::ios_base::openmode which = std::ios_base::in | std::ios_base::out ) {

        //mildly unsafe code
        if (dir == std::ios_base::cur) {
            if (which & std::ios_base::in)  this->gbump(off);
            if (which & std::ios_base::out) this->pbump(off);
        } else if (dir == std::ios_base::end) {
            if (which & std::ios_base::in)  this->setg(this->eback(), this->egptr() + off, this->egptr());
            if (which & std::ios_base::out) this->setp(ptr + len + off, ptr + len);
        } else if (dir == std::ios_base::beg) {
            if (which & std::ios_base::in)  this->setg(this->eback(), this->eback() + off, this->egptr());
            if (which & std::ios_base::out) this->setp(ptr + off, ptr + len);
        }
        return (which & std::ios_base::in) ? this->gptr() - this->eback() : this->pptr() - this->pbase();
    }

    base_sbuf::pos_type seekpos( base_sbuf::pos_type pos,
        std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {

        return this->seekoff(pos, std::ios_base::beg, which);
    }

private:
    CharT* ptr;
    size_t len;
};
