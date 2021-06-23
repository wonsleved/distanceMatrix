#include <iostream>
#include <vector>

using std::vector;

class Matrix {
private:
    vector<vector<int>> m_matrix;
public:
    Matrix(vector<vector<int>> matrix);
    int size() const;
    void print() const;
    Matrix& XOR(const Matrix& another);
    Matrix& pow(int pow);
    Matrix& clear();
    char isComplete();
    Matrix& operator = (const Matrix& another); // Поверхностное копирование
    Matrix& operator * (const Matrix& another);
    Matrix& operator *= (int num);
    Matrix& operator + (const Matrix& another);
    Matrix& operator += (const Matrix& another);
};

Matrix::Matrix(vector<vector<int>> matrix) {
    vector<int> tmp;
    for (int i = 0; i < matrix.size(); i++) {
        tmp.clear();
        for (int j = 0; j < matrix.size(); j++)
            tmp.push_back(matrix[i][j]);

        m_matrix.push_back(tmp);
    }
}

Matrix& Matrix::clear() {
    m_matrix.clear();
    return *this;
}

int Matrix::size() const {
    return m_matrix.size();
}

void Matrix::print() const {
    std::cout << std::endl;
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < size(); j++)
            std::cout << m_matrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Matrix& Matrix::operator = (const Matrix& another) {
    vector<int> tmp;
    for (int i = 0; i < another.size(); i++) {
        tmp.clear();
        for (int j = 0; j < another.size(); j++)
            tmp.push_back(another.m_matrix[i][j]);

        m_matrix.push_back(tmp);
    }
    return *this;
}

Matrix& Matrix::operator + (const Matrix &another) {
    if (another.size() != size()) {
        std::cerr << "Sizes are not equal!\n" << std::endl;
        exit(0);
    }
    vector<vector<int>> vec;

    vector<int> tmp;
    for (int i = 0; i < another.size(); i++) {
        tmp.clear();
        for (int j = 0; j < another.size(); j++)
            tmp.push_back(another.m_matrix[i][j] + m_matrix[i][j]);
        vec.push_back(tmp);
    }

    Matrix* result = new Matrix(vec);
    return *result;
}

Matrix& Matrix::operator += (const Matrix &another) {
    if (another.size() != size()) {
        std::cerr << "Sizes are not equal!\n" << std::endl;
        exit(0);
    }

    for (int i = 0; i < size(); i++)
        for (int j = 0; j < size(); j++)
            m_matrix[i][j] = another.m_matrix[i][j] + m_matrix[i][j];

    return *this;
}

Matrix& Matrix::operator *= (int num) {

    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < size(); j++)
            m_matrix[i][j] = num * m_matrix[i][j];
    }

    return *this;
}

Matrix& Matrix::operator * (const Matrix& another) {
    vector<vector<int>> vec;
    vector<int> tmp;
    int sum;
    for (int i = 0; i < another.size(); i++) {
        tmp.clear();
        sum = 0;
        for (int j = 0; j < another.size(); j++) {

            for (int k = 0; k < another.size(); k++)
                sum += i == j ? 0 : m_matrix[i][k] * another.m_matrix[k][j];

            if (sum > 0)
                sum = 1;

            tmp.push_back(sum);
            sum = 0;
        }
        vec.push_back(tmp);
    }

    Matrix* result = new Matrix(vec);
    return *result;
}

Matrix& Matrix::XOR(const Matrix& another) {

    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < size(); j++) {
            if (another.m_matrix[i][j] && m_matrix[i][j])
                m_matrix[i][j] = 0;
        }
    }
    return *this;
}

Matrix& Matrix::pow(int pow) {
    vector<vector<int>> vec;
    vector<int> tmp;
    int sum;
    Matrix tmpM = *this;

    while(--pow) {
        vec.clear();
        for (int i = 0; i < size(); i++) {
            tmp.clear();
            sum = 0;
            for (int j = 0; j < size(); j++) {
                for (int k = 0; k < size(); k++)
                    sum += i == j ? 0 : tmpM.m_matrix[i][k] * m_matrix[k][j];

                if (sum > 0)
                    sum = 1;

                tmp.push_back(sum);
                sum = 0;
            }
            vec.push_back(tmp);
        }

        tmpM.m_matrix.clear();
        tmpM = Matrix(vec);
    }


    m_matrix = tmpM.m_matrix;

    return *this;
}

char Matrix::isComplete() {
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < size(); j++) {
            if (i != j && m_matrix[i][j] == 0)
                return 0;
        }
    }
    return 1;
}


int main() {
    vector<vector<int>> vec;
    vector<int> tmp;
    int t;
    int size;
    std::cout << "Enter size: ";
    std::cin >> size;
    std::cout << std::endl;

    t = 0;
    for (int i = 0; i < size; i++) {
        tmp.clear();
        for (int j = 0; j < size; j++) {
            tmp.push_back(t);
        }
        vec.push_back(tmp);
    }

    int count;
    for (int i = 0; i < size; i++) {
        std::cout << "Enter count for " << i + 1 << " node: ";
        std::cin >> count;
        for (int j = 0; j < count; j++) {
            std::cout << j + 1 << " | Enter connected node: ";
            std::cin >> t;
            vec[i][t-1] = 1;
        }
    }



    Matrix input(vec);
    Matrix res(vec);
    Matrix tmpM(vec);

    input.print();

    for (int i = 2; i < size; i++) {
        tmpM.pow(i).XOR(res) *= i;
        res += tmpM;

        if (res.isComplete())
            break;

        tmpM.clear() = input;
    }

    res.print();

    return 0;
}
