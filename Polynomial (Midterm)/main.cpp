#include "Polynomial.hpp"
Polynomial readPolynomial() {
    Polynomial poly;
    int degree;
    cout << "Degree of your polynomial: ";
    cin >> degree;
    cout << endl;

    for (int i = 0; i <= degree; i++) {
        int coef;
        cout << "Coef of term with exponent " << i << ": ";
        cin >> coef;
        poly.setCoef(i, coef);
    }
    return poly;
}

void print_menu( ) {
    cout << endl;
    cout << "The following choices are available: " << endl;
    cout << " C Clear a polynomial" << endl;
    cout << " E Evaluate a polynomial" << endl;
    cout << " P Print a polynomial with degree" << endl;
    cout << " S Set a polynomial" << endl;
    cout << " + Add 2 polynomials" << endl; 
    cout << " - Subtract" << endl; 
    cout << " * Multiply" << endl;
    cout << " Q Quit this test program" << endl;
}

int main( ) {
    char choice; // Command entered by the user
    int num, exp;
    double value;
    Polynomial poly1, poly2;
    cout << "creating 2 polynomials" << endl;
    cout << "Initialize polynomial 1" << endl;
    poly1 = readPolynomial( );
    cout << "Initialize polynomial 2" << endl;
    poly2 = readPolynomial( );
    print_menu( );

    do {
        cout << "Enter choice: ";
        cin >> choice;
        choice = toupper(choice);
        switch (choice)
        {

        case 'M': // menu
        print_menu( );
        break;
        case 'C': // clear
        cout << "Clearing polynomial 1" << endl;
        poly1.clear( );
        cout << "Clearing polynomial 2" << endl;
        poly2.clear( );
        break; 

        case 'E': // evaluate
        double choice;
        cout << "Evaluate polynomials at what x: ";
        cin >> choice;

        cout << "Polynomial 1: " << poly1.evaluate(choice) << endl;
        cout << "Polynomial 2: " << poly2.evaluate(choice) << endl;
        break;

        case 'P': // print polynomial
        cout << "Print polynomial 1 or 2: ";
        cin >> num;
        if ( num == 1 ) {
        cout << "poly1 is " << poly1 << endl;
        } else if ( num == 2 ) {
        cout << "poly2 is " << poly2 << endl;
        } else {
        cout << "There are only 2 polynomials - 1 and 2" << endl;
        break;
        }

        case 'S': // set a polynomial
        cout << "Set polynomial 1 or 2: ";
        cin >> num;
        if ( num == 1 )
        {
        cout << "Enter exponent to select term (or a negative number to quit): ";
        cin >> exp;
        while ( exp >= 0 )
        { 
        cout << "Enter value of coefficient: ";
        cin >> value;
        poly1.setCoef( exp, value );
        cout << "Enter exponent to select term (or a -1 to quit): ";
        cin >> exp;   
        }

        cout << "poly1 is " << poly1 << endl;


        } else if ( num == 2 ) {
        cout << "Enter exponent to select term (or a negative number to quit): ";
        cin >> exp;
        while ( exp >= 0 )
        {
        cout << "Enter value of coefficient: ";
        cin >> value;
        poly1.setCoef( exp, value );
        cout << "Enter exponent to select term (or a -1 to quit): ";
        cin >> exp;
        }

        cout << "poly2 is " << poly2 << endl;  
        } else {
        cout << "There are only 2 polynomials - 1 and 2" << endl;
        break;

        case '+': // add polynomials 1 and 2
        cout << "The sum of " << poly1 << endl;
        cout << " and " << poly2 << endl;
        cout << " is " << (poly1 + poly2) << endl;
        break;

        case '-': // sub polynomials 1 and 2
        cout << "The difference of " << poly1 << endl;
        cout << " and " << poly2 << endl;
        cout << " is " << (poly1 - poly2) << endl;
        break;

        case '*': // multiply polynomials 1 and 2
        cout << "The product of " << poly1 << endl;
        cout << " and " << poly2 << endl;
        cout << " is " << (poly1 * poly2) << endl;
        break;

        case 'Q':
        cout << "Test program ended." << endl;
        break;

        default:
        cout << choice << " is invalid." << endl;
        }
    }
    } while ((choice != 'Q'));

    return EXIT_SUCCESS;
}