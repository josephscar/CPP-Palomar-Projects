#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAX_DEGREE = 10;
// Polynomial class header file
// Polynomial.hpp

struct Terms {
    int exponent;
    float coefficient;
    Terms(int exp, float coef) : exponent(exp), coefficient(coef) {}
    bool operator<(const Terms& other) const {
        return exponent < other.exponent;
    }
};

class Polynomial {
    private:
    vector<Terms> polyTerms;
    int degree = -1;

    public:
    // CONSTRUCTORS
    public:
    // Default constructor.
    Polynomial() {}
    // Constructor that takes a vector of Terms. Useful for initializing a Polynomial with multiple terms.
    Polynomial(const std::vector<Terms>& terms) : degree(-1) {
        for (const auto& term : terms) {
            setCoef(term.exponent, term.coefficient);
        }
        cleanAndSortTerms();
    }
    // Copy constructor.
    Polynomial(const Polynomial& other) : polyTerms(other.polyTerms), degree(other.degree) {}


    // MODIFICATION MEMBER FUNCTIONS
    // setCoef( ) - set a coefficient of the polynomial
    // Precondition: The exponent k is less than or equal to MAX_DEGREE.
    // Postcondition: The coefficient of the x^k term has been set to value.
    // The degree of the polynomial has been adjusted as necessary.
    void setCoef(int exponent, float value) {
        // Check if the given exponent exceeds the maximum degree allowed for the polynomial
        // If it does, throw an exception to indicate invalid input
        if (exponent > MAX_DEGREE) { 
            throw invalid_argument("Exponent exceeds the maximum allowed degree.");
        }

        // Attempt to find an existing term in the polynomial with the given exponent
        // The lambda function provided to find_if checks each term to see if its exponent matches the one we're setting
        auto find = find_if(polyTerms.begin(), polyTerms.end(), [exponent](const Terms& t) { 
            return t.exponent == exponent; 
        });

        // If a term with the specified exponent is found, update its coefficient
        if (find != polyTerms.end()) {
            find->coefficient = value;
        } else {
            // If no term with the specified exponent exists, create a new term with the given exponent and coefficient
            // and add it to the list of polynomial terms
            polyTerms.push_back(Terms(exponent, value));
        }

        // After updating the polynomial, clean and sort its terms
        // This might involve removing terms with a coefficient of zero and ensuring that terms are in ascending order
        // by their exponent. This step is crucial for maintaining the integrity and correctness of the polynomial's representation.
        cleanAndSortTerms();
    }

    // clear - set all coefficients to zero
    // Postcondition: All coefficients of the polynomial have been set to zero
    // and the degree has been set to -1.
    void clear( ){
        polyTerms.clear();
        degree = -1;
    }

    // ACCESSOR MEMBER FUNCTIONS

    // getCoef( ) - returns a coefficient
    // double getCoef( int k ) const;
    // Postcondition: If k is less than or equal to the degree of the polynomial,
    // the return value is the coefficient of x^k. Otherwise the return value is zero.
   double getCoef(int exponent) const {
        auto find = find_if(polyTerms.begin(), polyTerms.end(), [exponent](const Terms& t) { return t.exponent == exponent; });
        if (find != polyTerms.end()) {
            return find->coefficient;
        }
        return 0;
    }

    // getDegree( ) - returns the degree
    // Postcondition: The return value is the degree of the polynomial.
    int getDegree() const{
        return degree;
    }

    // evaluate( ) - evaluate the polynomial
    // Postcondition: The return value is the value of the polynomial at x = value.4
    double evaluate(double value) const{
        // Begin by adding the constant
        double result = 0;

        for (const auto& term : polyTerms){
            double temp = value;
            if (term.exponent == 0) {
                result += term.coefficient;
                continue;
            }
            // Raise the input value by the exponent
            for (int i = 0; i <= term.exponent; i++){
                temp *= value;
            }
            // Multiply the coefficient by the input value ^ exponent
            // Continue with sum
            result += term.coefficient * (temp); 
            
        }
        // Output summation
        return result;
    } 

    // Defines the sum of two polynomials
    Polynomial operator+ (Polynomial const & rhs) const{ 
        Polynomial result(*this);
        for (const auto& term : rhs.polyTerms) {
            result.setCoef(term.exponent, result.getCoef(term.exponent) + term.coefficient);
        }
        return result;
    }

    Polynomial operator- (Polynomial const & rhs) const{ 
        Polynomial result(*this);
        for (const auto& term : rhs.polyTerms) {
            result.setCoef(term.exponent, result.getCoef(term.exponent) - term.coefficient);
        }
        return result;
    }


    // Defines the product of two polynomials
    Polynomial operator* (Polynomial const & rhs) const{ 
        // Start with an empty polynomial to accumulate the result
        Polynomial result;

        // Multiply each term of the first polynomial (lhs, represented by 'this') 
        // by each term of the second polynomial (rhs)
        // This is analogous to the FOIL method for binomials, but extended to polynomials of any degree
        for (const auto& lhsTerm : this->polyTerms) {
            for (const auto& rhsTerm : rhs.polyTerms) {
                // Combine the exponents of the terms being multiplied
                int combineExp = lhsTerm.exponent + rhsTerm.exponent;
                // Multiply the coefficients of the terms being multiplied
                double combineCoef = lhsTerm.coefficient * rhsTerm.coefficient;

                // Attempt to find an existing term in the result polynomial with the combined exponent
                auto find = find_if(result.polyTerms.begin(), result.polyTerms.end(),
                                    [combineExp](const Terms& term) { return term.exponent == combineExp; });

                // If a term with this combined exponent already exists in the result, 
                // add the combined coefficient to its existing coefficient
                if (find != result.polyTerms.end()) {
                    find->coefficient += combineCoef;
                } else {
                    // If no such term exists, add a new term to the result polynomial 
                    // with the combined exponent and coefficient
                    result.polyTerms.push_back(Terms(combineExp, combineCoef));
                }
            }   
        }
        // After combining all terms, clean and sort the terms of the result polynomial
        // This step ensures that the polynomial is in canonical form, 
        // with terms ordered by increasing exponent and no duplicate exponents
        result.cleanAndSortTerms();

        // Return the resultant polynomial after multiplication
        return result;
    }


     
// Defines the assignment operator
Polynomial& operator=(const Polynomial& rhs) {
        // Simply sets the instance variable of the lhs equal to the rhs
        if (this != &rhs) {
            polyTerms = rhs.polyTerms;
            degree = rhs.degree;
        }
        return *this;
    }

void cleanAndSortTerms() {
    // Remove terms with a coefficient of 0
    // This step ensures that the polynomial does not contain any terms that do not contribute to its value
    polyTerms.erase(remove_if(polyTerms.begin(), polyTerms.end(), [](const Terms& term) {
        return term.coefficient == 0; // Predicate for identifying zero-coefficient terms
    }), polyTerms.end()); // Erase-remove idiom to remove terms that match the predicate

    // Sort the remaining terms in descending order by their exponents
    // This order is chosen to make the polynomial's representation more intuitive,
    // especially for human readers, and to ensure consistency in operations like addition, subtraction, and multiplication
    sort(polyTerms.begin(), polyTerms.end(), [](const Terms& a, const Terms& b) {
        return a.exponent > b.exponent; // Comparator for sorting terms by descending exponent
    });

    // Update the polynomial's degree to reflect the highest exponent term present after cleaning and sorting
    // If the polynomial is now empty (all terms were zero and removed), set the degree to -1 to indicate an empty polynomial
    degree = !polyTerms.empty() ? polyTerms.front().exponent : -1;
}

bool operator==(const Polynomial& rhs) const {
    // Fast fail: Check if the number of terms or the degrees of the two polynomials differ
    // If they do, the polynomials cannot be equal
    if (polyTerms.size() != rhs.polyTerms.size() || degree != rhs.degree) {
        return false;
    }

    // Compare each term of the polynomials one by one for equality
    // This requires that the terms are in the same order, which should be ensured by prior sorting
    for (size_t i = 0; i < polyTerms.size(); ++i) {
        // Compare both the exponents and coefficients of corresponding terms
        // If either differs, the polynomials are not equal
        if (polyTerms[i].exponent != rhs.polyTerms[i].exponent ||            
            polyTerms[i].coefficient != rhs.polyTerms[i].coefficient) {
            return false;
        }
    }
    // If all terms match in exponent and coefficient, the polynomials are considered equal
    return true;
}


    friend ostream& operator<<(ostream& os, const Polynomial& p);
};

// NON-MEMBER FUNCTIONS

// operator<<( ) - display the polynomial
// ostream & operator<<(ostream & out, const Polynomial & p);
// Postcondition: A character representation of Polynomial p has been inserted into
// output stream out.
ostream& operator<<(ostream& os, const Polynomial& p) {
    bool isFirst = true;
    for (const auto& term : p.polyTerms) {
        if (!isFirst) {
            os << " + ";
        } else {
            isFirst = false;
        }
        os << term.coefficient << "x^" << term.exponent;
    }
    return os;
}