struct polynomial : vector<complex<double>> {
  using super = vector<complex<double>>;
  using super::super;

  polynomial operator* (polynomial v) {
    const int sz = 1 << __lg(this->size() + v.size() - 1) + 1;
    this->resize(sz); fft(this->begin(), this->end());
    v.resize(sz); fft(v.begin(), v.end());
    for(int i = 0;i < sz;i++) (*this)[i] *= v[i];
    fft(this->begin(), this->end(), true);
    return *this;
  }
};