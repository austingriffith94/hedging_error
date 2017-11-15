# hedging_error
## Hedging Error and Profit and Loss Calculations
    This series of classes and code solves for:
    - value
    - option price
    - delta
    - profit and loss
    - cumulative hedging error
    for a given of a set of stock prices and options.

    There are csvs provided that have historical values.
    - interest rates
    - sec prices of Alphabet/Google stocks
    - option prices for Alphabet/Google

    The output of the function is a results csv.
    It holds:
    - spot price
    - value of the option
    - implied volatility
    - delta value
    - cumulative hedging error
    - profit and loss
    all per the date range provided.

    The dates can be altered in the main.cpp code if the user desires.

# Class Explanations:
## stdnormalcdf.h and stdnormalcdf.cpp:
    This is the class that solves for the standard normal approximation of an input value.
    The class is initialized with only a single value.
    In this case, it will often be the d1 value from the Black-Scholes class.
    The class uses a single function, and a private variable created from the initialized input value.
    When the Nx function is run, constant values used in the approximation of the Z value are created.
    Also, a 'B' value is created. It simply represents 1/√2π used in the approximation equation.
    The equation solves for the standard normal approximation of the input value.
    If the value was negative, it adjusts accordingly.
    The class can approximate the standard normal distribution of a value to within 6 decimal places.

## black.h and black.cpp
    These files hold the Black-Scholes class and respective equations.
    The private variables are time to expiration, strike price, spot price, interest rate and volatility.
    The d1 value and d2 value are public, and solved immediately upon initialization of the class for ease of access.
    Functions in the black file solve for the value of the put and call option, and the delta value.
    Put and call option functions are the Black-Scholes formula.
    In the calculation, the stdnormalcdf.h function is used to determine the standard normal approximation of d1 and d2.
    These values are then used with the initialized private variables to get the call or put value.
    The delta is the absolute value of the standard normal approximation of d1 by the exponential of
    dividends and time to expiration.
    If dividends are zero, this can simply be viewed as the normal approximation of d1 for call options.

## reader.h and reader.cpp
    The reader files are meant to read the csv, and hold the vector read locally to prevent clutter in the main file.
    Public variables include vectors that hold the values from the interest, sec_GOOG, and op_GOOG csv files.
    There is also the calculated days to expiration and days to trade.
    However, the latter is not used in the application of this assignment.

    The interest_input function using a simple while loop to read an interest file while the csv is open.
    It takes a line from the csv, and taking the string from the start of the line till the first comma,
    not including the comma.
    It then looks for a “-“, which is present in all date values, but not the header.
    It will read the date value and rate value, and updates the respective public vector with the value.
    This same logic is used in the sec_input class function, only it reads the sec csv file.

    The op_input function reads the op csv.
    It starts with a getline command before the while loop to skip the header of the file.
    Once in the while loop, it takes a line from the csv (now in the body, not header).
    The line is then passed into a string stream, and getline functions are used to parse the data by comma.
    Each iteration of getline gets a new set of variables, which are bumped to their respective vectors.

    The trimmer function is used to clean the vectors read from the csv with an input of strings:
    - start date
    - end date
    - expiration date
    It outputs:
    - interest rate vector
    - price vector
    - date vector
    each of which go from the specified start to end dates.

    The loop parses through the sec date vector, looking for a date that matches the start, end and expiration date.
    If that value is found, it gives the location of that date value.
    That location is used to section off the sec price and interest rate vectors from the start to the end values.
    For the expiration date, there is the issue of it often times falling on weekends.
    In order to find the days to expiration, a nested if else statement was used.
    The logic first finds when the month substrings matched.
    The day value is then changed to a double. If the day values matched, then that is the expiration location.
    If the day from the date vector jumped above the expiration day, then that is the expiration location.

    For the bid and offer functions, the inputs are:
    - a date
    - expiration date
    - strike price
    - option type

    A for loop runs through the op vectors, and compares the input values for the function.
    When all the values match, the location of the bid and offer values are found
    This location is the output, and used to find the value in the vector.

## hedge.h and hedge.cpp
    The hedge class is used to determine the implied volatility, delta, hedge error and profit and loss for the portfolio.
    The class is initialized with a set of variables:
    - price vector (from the sec file)
    - interest vector (from the interest file)
    - p vector (the average of the bid and offer values)
    - dates vector
    - strike
    - expiration time
    - volatility
    - dividends

    The pass private variable is set to 1/252, the passing of a single workday.
    The class vectors are:
    - hedging error
    - delta
    - profit and loss
    - implied volatility

    The volatility function is set to only run for 100 iterations, to reduce run time should the volatility not converge.
    The convergence value is set to 0.000001.
    A for loop is then run for size of the price vector.
    Then, the vega for the respective price and interest rate is calculated, as well as the estimated initial sigma value.
    Once the convergence value is met, the sigma value is added, and expiration value is updated.
    The private variables are:
    - spot
    - strike
    - time to expiration
    - interest rate
    - volatility
    - iterations
    - hedging error vector
    - profit and loss vector
    - the call price vector
    - the option price vector
    - delta vector

    In the error function, a for loop starts at 1, and continues till the iteration count is met.
    At the start of the loop, the price series function is called, and creates a new price using the prior price value.
    The black class constructor creates two versions of the class, with the old price and new price.
    Using the new price constructor, the delta value of the new price is called.
    This new delta is set into the delta vector.
    The old delta calculates the new B value
    Then, hedging error and profit and loss can be calculated, and their respective vectors are updated.
    The call price and spot price are also updated.
    The time to expiration value is reduced by a passing day.
    The price, delta and B values calculated from this iteration are set as the old value for the subsequent calculation.
    The loop is ended, and continued until completion.

