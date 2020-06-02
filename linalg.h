#ifndef __LINALG_H__
#define __LINALG_H__

#include <cassert>
#include <iostream>
#include <cmath>

template <typename T, size_t ROWS, size_t COLS>
class Matrix {
    private:
        T data_[ROWS][COLS];
    public:
        // Constructors
        Matrix() {
            for (size_t i = 0; i < ROWS; i++) {
                for (size_t j = 0; j < COLS; j++) {
                    data_[i][j] = T();
                }
            }
        }
        Matrix(const T data_[ROWS][COLS]) {
            for (size_t i = 0; i < ROWS; i++) {
                for (size_t j = 0; j < COLS; j++) {
                    this->data_[i][j] = data_[i][j];
                }
            }
        }
        // Destructor
        ~Matrix() {}
        // Access Operators
        T& operator()(const size_t i, const size_t j) {
            assert(i < ROWS && j < COLS);
            return this->data_[i][j];
        }
        const T& operator()(const size_t i, const size_t j) const {
            assert(i < ROWS && j < COLS);
            return this->data_[i][j];
        }
        // Unary Operators
        Matrix<T, COLS, ROWS> transpose() {
            Matrix<T, COLS, ROWS> result;
            for (size_t i = 0; i < ROWS; i++) {
                for (size_t j = 0; j < COLS; j++) {
                    result(j, i) = this->data_[i][j];
                }
            }
            return result;
        }
};

template <typename T, size_t ROWS>
class Matrix<T, ROWS, 1> {
    private:
        T data_[ROWS];
    public:
        // Constructors
        Matrix() {
            for (size_t i = 0; i < ROWS; i++) {
                data_[i] = T();
            }
        }
        Matrix(const T data_[ROWS]) {
            for (size_t i = 0; i < ROWS; i++) {
                this->data_[i] = data_[i];
            }
        }
        // Destructor
        ~Matrix() {}
        // Access Operators
        T& operator[](const size_t i) {
            assert(i < ROWS);
            return this->data_[i];
        }
        const T& operator[](const size_t i) const {
            assert(i < ROWS);
            return this->data_[i];
        }
};

template <typename T>
class Matrix<T, 2, 1> {
    private:
        T data_[2];
    public:
        // Constructors
        Matrix() {
            for (size_t i = 0; i < 2; i++) {
                data_[i] = T();
            }
        }
        Matrix(const T data_[2]) {
            for (size_t i = 0; i < 2; i++) {
                this->data_[i] = data_[i];
            }
        }
        Matrix(const T x, const T y) {
            this->data_[0] = x;
            this->data_[1] = y;
        }
        // Destructor
        ~Matrix() {}
        // Access Operators
        T& operator[](const size_t i) {
            assert(i < 2);
            return this->data_[i];
        }
        const T& operator[](const size_t i) const {
            assert(i < 2);
            return this->data_[i];
        }
};

template <typename T>
class Matrix<T, 3, 1> {
    private:
        T data_[3];
    public:
        // Constructors
        Matrix() {
            for (size_t i = 0; i < 3; i++) {
                data_[i] = T();
            }
        }
        Matrix(const T data_[2]) {
            for (size_t i = 0; i < 3; i++) {
                this->data_[i] = data_[i];
            }
        }
        Matrix(const T x, const T y, const T z) {
            this->data_[0] = x;
            this->data_[1] = y;
            this->data_[2] = z;
        }
        // Destructor
        ~Matrix() {}
        // Access Operators
        T& operator[](const size_t i) {
            assert(i < 3);
            return this->data_[i];
        }
        const T& operator[](const size_t i) const {
            assert(i < 3);
            return this->data_[i];
        }
};

// Unary Operators
template<typename T, size_t ROWS>
float norm(const Matrix<T, ROWS, 1> a) {
    return sqrt(dot(a, a));
}

template<typename T, size_t ROWS>
Matrix<float, ROWS, 1> normalize(const Matrix<T, ROWS, 1> a) {
    Matrix<float, ROWS, 1> result;
    float norm_ = norm(a);
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = a[i] / norm_;
    }
    return result;
}

// Binary Operators
template <typename T, size_t ROWS>
T dot(const Matrix<T, ROWS, 1> a, const Matrix<T, ROWS, 1> b) {
    T sum = 0;
    for (size_t i = 0; i < ROWS; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

template <typename T>
Matrix<float, 3, 1> cross(const Matrix<T, 3, 1> a, const Matrix<T, 3, 1> b) {
    T x = a[1]*b[2] - a[2]*b[1];
    T y = a[2]*b[0] - a[0]*b[2];
    T z = a[0]*b[1] - a[1]*b[0];
    Matrix<float, 3, 1> result(x, y, z);
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& a, const Matrix<T, ROWS, COLS>&b) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = a(i, j) + b(i, j);
        }
    }
    return result;
}

template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator+(const Matrix<T, ROWS, 1>& a, const Matrix<T, ROWS, 1>&b) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = a[i] + b[i];
    }
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& a, const Matrix<T, ROWS, COLS>& b) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = a(i, j) - b(i, j);
        }
    }
    return result;
}

template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator-(const Matrix<T, ROWS, 1>& a, const Matrix<T, ROWS, 1>& b) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = a[i] - b[i];
    }
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& m, const T& s) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = m(i, j) + s;
        }
    }
    return result;
}


template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator+(const T& s, const Matrix<T, ROWS, COLS>& m) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j <=COLS; j++) {
            result(i, j) = m(i, j) + s;
        }
    }
    return result;
}

template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator+(const Matrix<T, ROWS, 1>& m, const T& s) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = m[i] + s;
    }
    return result;
}


template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator+(const T& s, const Matrix<T, ROWS, 1>& m) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = m[i] + s;
    }
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& m, const T& s) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = m(i, j) - s;
        }
    }
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator-(const T& s, const Matrix<T, ROWS, COLS>& m) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = m(i, j) - s;
        }
    }
    return result;
}

template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator-(const Matrix<T, ROWS, 1>& m, const T& s) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = m[i] - s;
    }
    return result;
}


template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator-(const T& s, const Matrix<T, ROWS, 1>& m) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = m[i] - s;
    }
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& m, const T& s) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = m(i, j) * s;
        }
    }
    return result;
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS> operator*(const T& s, const Matrix<T, ROWS, COLS>& m) {
    Matrix<T, ROWS, COLS> result;
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            result(i, j) = m(i, j) * s;
        }
    }
    return result;
}

template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator*(const Matrix<T, ROWS, 1>& m, const T& s) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = m[i] * s;
    }
    return result;
}


template <typename T, size_t ROWS>
Matrix<T, ROWS, 1> operator*(const T& s, const Matrix<T, ROWS, 1>& m) {
    Matrix<T, ROWS, 1> result;
    for (size_t i = 0; i < ROWS; i++) {
        result[i] = m[i] * s;
    }
    return result;
}

// I/O
template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, COLS>& m) {
    os << "[";
    for (size_t i = 0; i < ROWS; i++) {
        os << "[";
        for (size_t j = 0; j < COLS; j++) {
            os << m(i, j);
            if (j != COLS-1) {
                os << ", ";
            }
        }
        os << "]";
        if (i != ROWS-1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template <typename T, size_t ROWS>
std::ostream& operator<<(std::ostream& os, const Matrix<T, ROWS, 1>& m) {
    os << "[";
    for (size_t i = 0; i < ROWS; i++) {
        os << m[i];
        if (i != ROWS-1) {
            os << "; ";
        }
    }
    os << "]";
    return os;
}

// Convenient typedefs
typedef Matrix<float, 2, 1> Vec2f;
typedef Matrix<int, 2, 1> Vec2i;
typedef Matrix<float, 3, 1> Vec3f;
typedef Matrix<int, 3, 1> Vec3i;

#endif //__LINALG_H__