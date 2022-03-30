#include "Matrix.hpp"
#include <cstdlib>

int main()
{
    std::cout << std::boolalpha;
    {
        std::cout << "[*****************************************************]" << std::endl;

        Matrix<int> A(6, 3);
        Matrix<int> B(3, 6);

        std::cout << "A(" << A.getRows() << ", " << A.getColumns() << ");" << std::endl;
        std::cout << "B(" << B.getRows() << ", " << B.getColumns() << ");" << std::endl;

        std::cout << "\nAB - " << A.isMultipliableBy(B) << std::endl;
        std::cout << "BA - " << B.isMultipliableBy(A) << std::endl;
    }
    {
        std::cout << "[*****************************************************]" << std::endl;

        Matrix<int> A(3, 5);
        Matrix<int> B(5, 7);

        std::cout << "A(" << A.getRows() << ", " << A.getColumns() << ");" << std::endl;
        std::cout << "B(" << B.getRows() << ", " << B.getColumns() << ");" << std::endl;

        std::cout << "\nAB - " << A.isMultipliableBy(B) << std::endl;
        std::cout << "BA - " << B.isMultipliableBy(A) << std::endl;

        srand(time(0));

        auto func = []()
        {
            return (rand() % 10 + 1);
        };

        A.random(func);
        B.random(func);
        std::cout << "---------------------------------------------------------" << std::endl;
        A.print();
        std::cout << "---------------------------------------------------------" << std::endl;
        B.print();
        std::cout << "---------------------------------------------------------" << std::endl;
        (A * B).print();
        std::cout << "---------------------------------------------------------" << std::endl;
        (A *= B).print();
        std::cout << "---------------------------------------------------------" << std::endl;
        A.print();
        std::cout << "---------------------------------------------------------" << std::endl;
        (A * 10).print();
        std::cout << "---------------------------------------------------------" << std::endl;
        A.print();
        std::cout << "---------------------------------------------------------" << std::endl;
        (A *= 10).print();
        std::cout << "---------------------------------------------------------" << std::endl;
        A.print();
    }
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        Matrix<int> A(3, 6);

        auto func = []()
        {
            return (rand() % 10);
        };

        A.random(func);
        A.print();
        std::cout << "---------------------------------------------------------" << std::endl;
        A.transpose().print();
    }

    return 0;
}