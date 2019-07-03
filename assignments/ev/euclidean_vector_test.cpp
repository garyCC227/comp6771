/*

  == Explanation and rational of testing ==
this test will have the coverage:
    1. function coverage: all the functions will be called in this test
    2. branch/ statement coverage: will use the special input for some functions, to test if that
        statement/expression/if_else branch been implemented? to see if is the expected output or not
In summary, by testing each functions, and cover all the possible input for each functions(so branch
 coverage), we would guarantee correctness for all the functions for this program.

 ---------------
 table of content for each test case(Too see detail, go the corresponding test case section)
 ---------------
 1. default constructor
*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

/*
 *  1. Test default constructor. How to test:
 *  after initialized the vector with default constructor,
 *  check dimension and magnitudes
 */
SCENARIO("Testing default constructor"){
    GIVEN("We will initialized all the possible way to use the default constructor"){
        WHEN("EuclidenVector a, dimension = 1, magnitudes[0] is 0"){
            EuclideanVector vec;
            REQUIRE(vec.GetNumDimensions() == 1);
            REQUIRE(vec[0] == 0);
        }

        WHEN("dimension is 0, dimension = 0, throw for maginitudes[0]"){
            EuclideanVector vec{0};
            REQUIRE(vec.GetNumDimensions() == 0);
            //if index 0 is not valid, we can say the whole vector is empty
            REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
        }

        WHEN("dimension is some positive int, such d = 10"){
            EuclideanVector vec{10};
            REQUIRE(vec.GetNumDimensions() == 10);
            for(int i = 0 ; i < 10; ++i){
                REQUIRE(vec[i] == 0);
            }
        }

        WHEN("variable is int type, d = 5"){
            int d{5};
            EuclideanVector vec{d};

            REQUIRE(vec.GetNumDimensions() == 5);
            for(int i = 0 ; i < 5; ++i){
                REQUIRE(vec[i] == 0);
            }
        }
    }
}

/*
 * 2. Test the constructor (int, double)
 *  -  check dimension and magnitudes
 */
SCENARIO("Testing constructor(d = int, m = double)"){
    GIVEN("all possible test cases"){
        WHEN("d = 0,  m is any numbers"){
            EuclideanVector vec{0, 5.5};
            REQUIRE(vec.GetNumDimensions() == 0);
            //if index 0 is not valid, we can say the whole vector is empty
            REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
        }

        WHEN("d = 5(any positive int), m = 5.5(any double number)"){
            EuclideanVector vec{5, 5.5};
            REQUIRE(vec.GetNumDimensions() == 5);
            for(int i=0; i<5; ++i){
                REQUIRE(vec[i] == 5.5);
            }
        }

        WHEN("variables has int and double type"){
            int d{5};
            double m{5.5};
            EuclideanVector vec{d, m};
            REQUIRE(vec.GetNumDimensions() == 5);
            for(int i=0; i<5; ++i){
                REQUIRE(vec[i] == 5.5);
            }
        }
    }
}

/*
 * 3. Test range constructor. with given a pair of vector iterator.
 *  -   check dimension and magnitudes
 */
SCENARIO("Testing range constructor"){
    GIVEN("all possible test cases for this constructor"){
        WHEN("empty vector, then we should have d = 0"){
            std::vector<double> temp;
            EuclideanVector vec{temp.begin(), temp.end()};

            REQUIRE(vec.GetNumDimensions() == 0);
            //if index 0 is not valid, we can say the whole vector is empty
            REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
        }

        WHEN("normal vector is given"){
            std::vector<double> temp{1,2,3,4,5,6};
            EuclideanVector vec{temp.begin(), temp.end()};

            REQUIRE(vec.GetNumDimensions() == static_cast<int>(temp.size()) );
            for(int i = 0 ; i < vec.GetNumDimensions(); ++i){
                REQUIRE(vec[i] == temp[i]);
            }
        }
    }
}


/*
 * 4. Test copy constructor
 *  -   compare old and new Euclidean vector
 */
SCENARIO("Testing copy constructor"){
    GIVEN("Given a old_vec"){
        EuclideanVector vec{5, 0.5};

        WHEN("copy old_vec to a new one, check d/m of the new one, and the old one"){
            EuclideanVector new_vec{vec};
            REQUIRE(vec == new_vec);
        }
    }
}

/*
 * 5. Test move constructor
 *  -   check dimension and m
 */
SCENARIO("Testing move constructor"){
    GIVEN("given a old_vec and a copy of it"){
        EuclideanVector old_vec{5,5.5};
        EuclideanVector copy_old_vec{old_vec};

        WHEN("using move constructor to create a new one"){
            EuclideanVector new_vec{std::move(old_vec)};
            REQUIRE(new_vec == copy_old_vec);
            // check old vector to default or not?
            REQUIRE(old_vec.GetNumDimensions() == 0);
            //if index 0 is not valid, we can say the whole vector is empty
            REQUIRE_THROWS_WITH(old_vec.at(0), "Index 0 is not valid for this EuclideanVector object" );

        }
    }
}

/*
 * 6. Test: copy assignment
 * -    check dimension and m
 */
SCENARIO("Testing copy assignment"){
    GIVEN("Given a old vector"){
        EuclideanVector old_vec{5,5.5};

        WHEN("self copy-> to test if that works"){
            REQUIRE_NOTHROW(old_vec = old_vec);
        }

        WHEN("copy with old_vec "){
            EuclideanVector new_vec{1,4.0};
            REQUIRE(new_vec.GetNumDimensions() == 1);
            REQUIRE(new_vec[0] == 4);

            new_vec = old_vec;
            REQUIRE(new_vec.GetNumDimensions() == 5);
            REQUIRE(new_vec == old_vec);
        }
    }
}

/*
 * 7. Test: move assignment
 * - check dimension and m with new_vec and old_vec
 */
SCENARIO("Testing move assignment"){
    GIVEN("Given a old_vec"){
        EuclideanVector old_vec{5, 5.5};

        WHEN("check if self assignment works"){
            REQUIRE_NOTHROW(old_vec = old_vec);
        }

        WHEN("move assignement to a new vector"){
            EuclideanVector new_vec{1,4.0};
            REQUIRE(new_vec.GetNumDimensions() == 1);
            REQUIRE(new_vec[0] == 4);

            new_vec = std::move(old_vec);
            REQUIRE(new_vec.GetNumDimensions() == 5);
            for(int i = 0; i < 5; ++i){
                REQUIRE(new_vec[i] == 5.5);
            }
            //check old_vec set back to default?
            REQUIRE(old_vec.GetNumDimensions() == 0);
            //check index 0, guarantee its magnitudes set back to default
            REQUIRE_THROWS_WITH(old_vec.at(0), "Index 0 is not valid for this EuclideanVector object");
        }
    }
}

/*
 * 8. Test: subscript operator (getter and setter)
 *  -   check getter and setter work after :
 *      1. initialized
 *      2. reassign by another vector
 *      3. (things didnt do: not-valid index)
 *          since we use `assert` instead of throw. and also normally subscript operator did not
 *          handle for invalid index error message.
 */
SCENARIO("Testing subscript operator"){
    GIVEN("a list of sub-test cases "){
        WHEN("use getter and setter after initialized a vector"){
            EuclideanVector vec{5};
            //test getter
            for(int i = 0; i < 5; ++i){
                REQUIRE(vec[i] == 0);
            }

            //test setter
            for(int i = 0; i < 5; ++i){
                REQUIRE_NOTHROW(vec[i] = 5);
            }
            for(int i = 0; i < 5; ++i){
                REQUIRE(vec[i] == 5);
            }
        }

        WHEN("use getter and setter after assignment "){
            EuclideanVector vec{5};
            EuclideanVector old_vec{4,5.5};
            vec = old_vec;

            //test getter
            for(int i = 0; i < 4; ++i){
                REQUIRE(vec[i] == 5.5);
            }

            //test setter
            for(int i = 0; i < 4; ++i){
                REQUIRE_NOTHROW(vec[i] = 5);
            }
            for(int i = 0; i < 4; ++i){
                REQUIRE(vec[i] == 5);
            }
        }

    }
}

/*
 * 9. test += operator: test cases
 *  1. dimensions no match
 *  2. normal += operator
 *  3. (Things not do, but CLion will cover it): += not EuclideanVector object
 */
SCENARIO("Testing += operator"){
    GIVEN("a vector to +="){
        EuclideanVector vec{5, 5.5};

        WHEN("when dimensions is not match"){
            EuclideanVector bad_vec{4, 4.0};
            REQUIRE_THROWS_WITH(vec+= bad_vec, "Dimensions of LHS(5) and RHS(4) do not match");
        }

        WHEN("normal += operation"){
            std::vector<double> input{1,2,3,4,5};
            EuclideanVector good_vec{input.begin(), input.end()};
            vec += good_vec;

            //require good_vec not change
            REQUIRE(good_vec.GetNumDimensions() == 5);
            for(int i=0; i < 5; ++i){
                REQUIRE(good_vec[i] == input[i]);
            }

            //require vec will be expected
            REQUIRE(vec.GetNumDimensions() == 5);
            for(int i = 0; i < 5; ++i){
                REQUIRE(vec[i] == (5.5 + input[i]));
            }
        }
    }
}

/*
 * 10. test -= operator
 *      1. dimensions no match
 *      2. normal += operator
 *      3. (Things not do, but CLion will cover it): += not EuclideanVector object
 */
SCENARIO("Testing -= operator"){
    GIVEN("a vector to -="){
        EuclideanVector vec{5, 5.5};

        WHEN("when dimensions is not match"){
            EuclideanVector bad_vec{4, 4.0};
            REQUIRE_THROWS_WITH(vec-= bad_vec, "Dimensions of LHS(5) and RHS(4) do not match");
        }

        WHEN("normal -= operation"){
            std::vector<double> input{1,2,3,4,5};
            EuclideanVector good_vec{input.begin(), input.end()};
            vec -= good_vec;

            //require good_vec not change
            REQUIRE(good_vec.GetNumDimensions() == 5);
            for(int i=0; i < 5; ++i){
                REQUIRE(good_vec[i] == input[i]);
            }

            //require vec will be expected
            REQUIRE(vec.GetNumDimensions() == 5);
            for(int i = 0; i < 5; ++i){
                REQUIRE(vec[i] == (5.5 - input[i]));
            }
        }
    }
}

/*
 * 11. Test *= operator:
 *  -   check expected output for input type is(since we have implicit type conversion, so )
 *      1. int
 *      2. double
 */
SCENARIO("Testing *= operator"){
    GIVEN("a list of tests case"){
        WHEN("input type is int"){
            int b{2};
            EuclideanVector vec{4, 4.5};
            vec *= b;

            REQUIRE(vec.GetNumDimensions() == 4);
            for(int i = 0 ; i < 4; ++i){
                REQUIRE(vec[i] == (4.5 * (2.0) ));
            }
        }

        WHEN("input type is double"){
            double b{2.5};
            EuclideanVector vec{4, 4.5};
            vec *= b;

            REQUIRE(vec.GetNumDimensions() == 4);
            for(int i = 0 ; i < 4; ++i){
                REQUIRE(vec[i] == (4.5 * 2.5));
            }
        }
    }
}

/*
 * 12. Test /= operator:
 *  -   check expected output for input type is(since we have implicit type conversion, so )
 *      1. int
 *      2. double
 *      3. input is 0
 */
SCENARIO("Testing /= operator"){
    GIVEN("a list of tests case"){
        WHEN("input type is int"){
            int b{2};
            EuclideanVector vec{4, 4.5};
            vec /= b;

            REQUIRE(vec.GetNumDimensions() == 4);
            for(int i = 0 ; i < 4; ++i){
            REQUIRE(vec[i] == (4.5 / (2.0) )); // since we have implicit type conversion
            }
        }

        WHEN("input type is double"){
            double b{2.5};
            EuclideanVector vec{4, 4.5};
            vec /= b;

            REQUIRE(vec.GetNumDimensions() == 4);
            for(int i = 0 ; i < 4; ++i){
                REQUIRE(vec[i] == (4.5 / 2.5));
            }
        }

        WHEN("input b == 0 "){
            double b{0};
            EuclideanVector vec{4, 4.5};
            REQUIRE_THROWS_WITH(vec /= b, "Invalid vector division by 0");
        }
    }
}

/*
 * 13.Test : std::vector conversion operator
 *  -   just check if is expected output
 */
SCENARIO("Test std::vector<double> type conversion"){
    GIVEN("a std::vector we want to convert to, and a Euclidean vector have same value"){
        std::vector<double> correct_vec = {4, 5, 6, 7, 8, 1};
        EuclideanVector vec {correct_vec.begin(), correct_vec.end()};

        WHEN("Euclidean vector to std::vector<double>"){
            auto output = static_cast<std::vector<double>>(vec);
            REQUIRE(output == correct_vec);
        }
    }
}

/*
 * 13.Test : std::list conversion operator
 *  -   just check if is expected output
 */
SCENARIO("Test std::list<double> type conversion"){
    GIVEN("a std::list we want to convert to, and a Euclidean vector have same value"){
        std::list<double> correct_list = {4.5, 4.5, 4.5, 4.5, 4.5, 4.5};
        EuclideanVector vec {6, 4.5};
        REQUIRE(correct_list.size() == 6);

        WHEN("Euclidean vector to std::vector<double>"){
            auto output = static_cast<std::list<double>>(vec);
            REQUIRE(output == correct_list);
        }
    }
}

/*
 * 14. test at() method.
 *      1. invalid index
 *      2. normal index
 *      3. index is double
 */
SCENARIO("Test at() method"){
    GIVEN("given a vector "){
        std::vector<double> temp{1, 2, 3, 4};
        EuclideanVector vec{temp.begin(), temp.end()};
        REQUIRE( (temp.size() == 4 && vec.GetNumDimensions() == 4) );

        WHEN("index is invalid"){
            int index1{-1};
            int index2{4};

            REQUIRE_THROWS_WITH(vec.at(index1), "Index -1 is not valid for this EuclideanVector object");
            REQUIRE_THROWS_WITH(vec.at(index2), "Index 4 is not valid for this EuclideanVector object");
        }

        WHEN("normal index"){
            int index{2};
            REQUIRE(vec.at(index) == 3);
        }

        WHEN("index type is double"){
            double index{2.5};
            // by implicit type conversion double to int in c++
            // should be index 2.5 -> 2. so we are checking vec.at(2)
            REQUIRE(vec.at(index) == 3);
        }
    }
}

/*
 * 15. test GetNumDimensions() methods
 *  -    check if is the expected output, after all the situations that might change the dimension
 *      1. after copy constructor
 *      2. after copy assignment
 *      3. after move constructor
 *      4. after move assignment
 *      5. normal constructor
 *      6. default constructor
 *      7. unit vector
 */
SCENARIO("Test GetNumDimensions() methods"){
    GIVEN("given a vector "){
        EuclideanVector temp_vec{4, 4.0};

        WHEN("7. create auto unit vector"){
            auto unit_vec = temp_vec.CreateUnitVector();
            REQUIRE(unit_vec.GetNumDimensions() == 4);
        }

        WHEN("6.default constructor"){
            EuclideanVector vec{5};
            REQUIRE(vec.GetNumDimensions() == 5);
        }

        WHEN("5.normal constructor"){
            REQUIRE(temp_vec.GetNumDimensions() == 4);
        }

        WHEN("4. move assignment"){
            EuclideanVector dest_vec{5, 5.5};
            EuclideanVector start_vec{4, 5.5};
            REQUIRE(start_vec.GetNumDimensions() == 4);
            start_vec = std::move(dest_vec);

            //check the dimension of start and destination vector
            REQUIRE(start_vec.GetNumDimensions() == 5);
            REQUIRE(dest_vec.GetNumDimensions() == 0);
        }

        WHEN("3.move constructor"){
            EuclideanVector dest_vec{5, 5.5};
            EuclideanVector start_vec = std::move(dest_vec);

            //check the dimension of start and destination vector
            REQUIRE(start_vec.GetNumDimensions() == 5);
            REQUIRE(dest_vec.GetNumDimensions() == 0);
        }

        WHEN("2.copy assignment"){
            EuclideanVector start_vec{1, 5.5};
            REQUIRE(start_vec.GetNumDimensions() == 1);

            start_vec = temp_vec;
            REQUIRE(start_vec.GetNumDimensions() == 4);
            REQUIRE(temp_vec.GetNumDimensions() == 4);
        }

        WHEN("1. copy constructor"){
            REQUIRE(temp_vec.GetNumDimensions() == 4);
            EuclideanVector vec{temp_vec};

            REQUIRE(vec.GetNumDimensions() == 4);
        }
    }
}

/*
 * 16. Test: GetEuclideanNorm()
 *  -   check if the normal value is correct
 *  - error case: dimension is 0
 */
SCENARIO("Test GetEuclideanNorm() .."){
    GIVEN("A list of normal value"){
        //norm for vector {2,3,5,6}
        double norm1 = sqrt( pow(2, 2) + pow(3,2) + pow(5,2) + pow(6,2) );
        //norm for magnitudes is double. for a vector{1.5, 3.5, 4, 4.5}
        double norm2 = sqrt( pow(1.5, 2) + pow(3.5,2) + pow(4,2) + pow(4.5,2) );

        WHEN("vector is {2, 3, 4, 5}"){
            std::vector<double> v1{2, 3, 5, 6};
            EuclideanVector vec{v1.begin(), v1.end()};

            REQUIRE(vec.GetEuclideanNorm() == norm1);
        }

        WHEN("vector is {1.5, 3.5, 4, 4.5}"){
            std::vector<double> v2{1.5, 3.5, 4, 4.5};
            EuclideanVector vec{v2.begin(), v2.end()};

            REQUIRE(vec.GetEuclideanNorm() == norm2);
        }

        WHEN("dimension is 0"){
            EuclideanVector vec{0};

            REQUIRE_THROWS_WITH(vec.GetEuclideanNorm(), "EuclideanVector with no dimensions does not have a norm");
        }
    }
}

/*
 * 17.Test: CreateUnitVector()
 * -    error case1: 0 dimension
 * -    error case2: norm is 0
 * -    magnitudes is negative, positive, normal vector -> end up for the normal of those unit vector is 1
 */
SCENARIO("Testing UnitVector()"){
    GIVEN("given the normal of all unit vector, which is 1"){
        int unit_norm{1};

        WHEN("dimension is 0"){
            EuclideanVector vec{0};
            REQUIRE_THROWS_WITH(vec.CreateUnitVector(), "EuclideanVector with no dimensions does not have a unit vector");
        }

        WHEN("the normal of original vector is 0, it cant create a unit vector as well"){
            // all magnitudes is 0, so normal will be 0
            EuclideanVector vec{5};
            REQUIRE(vec.GetEuclideanNorm() == 0);

            REQUIRE_THROWS_WITH(vec.CreateUnitVector(), "EuclideanVector with euclidean normal of 0 does not have a unit vector");
        }

        WHEN("a vector have all the magnitudes is negative"){
            std::vector<double> temp{-1, -2, -3, -4, -5};
            EuclideanVector vec{temp.begin(), temp.end()};

            REQUIRE(vec.CreateUnitVector().GetEuclideanNorm() == unit_norm);
        }

        WHEN("a vector have all positive magnitudes"){
            std::vector<double> temp{5, 10, 1.5, 15.5, 13};
            EuclideanVector vec{temp.begin(), temp.end()};

            REQUIRE(vec.CreateUnitVector().GetEuclideanNorm() == unit_norm);
        }

        WHEN("vector have positive and negative magnitudes"){
            std::vector<double> temp{ 5, 3.5, -2, 5, -4.5};
            EuclideanVector vec{temp.begin(), temp.end()};

            REQUIRE(vec.CreateUnitVector().GetEuclideanNorm() == unit_norm);
        }
    }
}

/*
 * 18. test == operator
 */
SCENARIO("Testing == operator"){
    GIVEN("given a vector to test"){
        std::vector<double> temp{2,3,4,5,6};
        EuclideanVector vec{temp.begin(), temp.end()};

        WHEN("two vector are not the same"){
            //dimension not the same
            EuclideanVector temp1{2, 5};
            EuclideanVector temp2{0};
            std::vector<double> temp3_v{1,3.0};
            EuclideanVector temp3{temp3_v.begin(), temp3_v.end()};

            REQUIRE_FALSE( (vec == temp1 && vec == temp2 && vec == temp3));

            //dimension same, but value not
            EuclideanVector temp4{5,5.5};
            EuclideanVector temp5{5};
            EuclideanVector temp6{vec};
            temp6[0] = 10;

            REQUIRE_FALSE( (vec == temp4 && vec == temp5 && vec == temp6) );
        }

        WHEN("two vector are same"){
            EuclideanVector same_vec{vec};

            REQUIRE(same_vec == vec);
        }
    }
}

/*
 * 19. test != operator
 */
SCENARIO("Testing != operator"){
    GIVEN("given a vector to test"){
        std::vector<double> temp{2,3,4,5,6};
        EuclideanVector vec{temp.begin(), temp.end()};

        WHEN("two vector are not the same"){
            //dimension not the same
            EuclideanVector temp1{2, 5};
            EuclideanVector temp2{0};
            std::vector<double> temp3_v{1,3.0};
            EuclideanVector temp3{temp3_v.begin(), temp3_v.end()};

            REQUIRE( (vec != temp1 && vec != temp2 && vec != temp3) );

            //dimension same, but value not
            EuclideanVector temp4{5,5.5};
            EuclideanVector temp5{5};
            EuclideanVector temp6{vec};
            temp6[0] = 10;

            REQUIRE( (vec != temp4 && vec != temp5 && vec != temp6) );
        }

        WHEN("two vector are same"){
            EuclideanVector same_vec{vec};

            REQUIRE_FALSE(same_vec != vec);
        }
    }
}

/*
 * 20. Test + operator
 *  -   different dimensions
 *  -   dimension 0 + dimension 0
 *  -   magnitudes are all 0
 *  -   normal + operation
 */
SCENARIO("Testing + operator"){
    GIVEN("a list of test cases"){
        WHEN("dimensions are not same"){
            EuclideanVector v1{0, 5};
            EuclideanVector v2{1, 5};

            REQUIRE_THROWS_WITH(v1+v2, "Dimensions of LHS(0) and RHS(1) do not match");
        }

        WHEN("dimension 0 + 0 -> still the vector itself"){
            EuclideanVector v1{0};
            EuclideanVector v2{0};

            REQUIRE( v1 == (v1 + v2));
        }

        WHEN("RHS vector has magnitudes are all 0, LHS is still LHS after +"){
            EuclideanVector v1{5, 5.5};
            EuclideanVector  v2{5};

            REQUIRE(v1 == (v1 + v2));
        }

        WHEN("two normal vector +"){
            EuclideanVector v1{5, 5.5};
            EuclideanVector v2{5, 1};
            EuclideanVector v3{5, 6.5};

            REQUIRE( v3 == (v1 + v2));
        }
    }
}

/*
 * 21. Test - operator
 *  -   different dimensions
 *  -   dimension 0 + dimension 0
 *  -   magnitudes are all 0
 *  -   normal + operation
 */
SCENARIO("Testing - operator"){
    GIVEN("a list of test cases"){
        WHEN("dimensions are not same"){
            EuclideanVector v1{0, 5};
            EuclideanVector v2{1, 5};

            REQUIRE_THROWS_WITH(v1-v2, "Dimensions of LHS(0) and RHS(1) do not match");
            }

        WHEN("dimension 0 - 0 -> still the vector itself"){
            EuclideanVector v1{0};
            EuclideanVector v2{0};

            REQUIRE( v1 == (v1 - v2));
        }

        WHEN("RHS vector has magnitudes are all 0, LHS is still LHS after -"){
            EuclideanVector v1{5, 5.5};
            EuclideanVector  v2{5};

            REQUIRE(v1 == (v1 - v2));
        }

        WHEN("two normal vector -"){
            EuclideanVector v1{5, 5.5};
            EuclideanVector v2{5, 1};
            EuclideanVector v3{5, 4.5};

            REQUIRE( v3 == (v1 - v2));
        }
    }
}

/*
 * 22. Test : * operator -> for dot product of two vector
 */