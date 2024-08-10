import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error



def Generate_Normal(mu, sigma, N):
    np.random.seed(712)
    return np.random.normal(mu, sigma, N)

def Generate_Data(ltrain, rtrain):
    nb_train = (int)((rtrain - ltrain) / 2 + 1)
    T1 = np.linspace(ltrain, rtrain, nb_train)
    R_T1_raw = 22 * np.exp(3100 * - (1/298 - 1/(T1+273)))
    epsilon = Generate_Normal(0, 0.5, nb_train)
    #epsilon = Generate_Normal(0, 5, (rtrain - ltrain) / 2 + 1)

    X_train = T1[:,np.newaxis]
    Y_train = (R_T1_raw + epsilon)[:,np.newaxis]

    T2 = np.concatenate([np.linspace(0, ltrain - 2, int((ltrain - 2) / 2 + 1)), np.linspace(rtrain, 100, int((100 - rtrain) / 2 + 1))])

    R_T2_raw = 22 * np.exp(3100 * - (1/298 - 1/(T2+273)))
    X_test = T2[:, np.newaxis]
    Y_test = (R_T2_raw)[:, np.newaxis]


    return X_train, Y_train, X_test, Y_test

def plotcurve():
    T1 = np.linspace(0, 100, 50)
    R_T1 = 22 * np.exp(3100 * - (1/298 - 1/(T1+273)))
    plt.plot(T1, R_T1)
    plt.xlabel('Temperature /$^\\circ C$ ')
    plt.ylabel('Resistance /$\Omega$')
    plt.title('Thermistor resistance characteristic curve')
    plt.show()

def polyfit(degree, X_train, Y_train, X_test, Y_test):
    polynomial = PolynomialFeatures(degree=degree)
    X_transformed = polynomial.fit_transform(X_train)

    lm = LinearRegression()
    reg = lm.fit(X_transformed, Y_train)

    y_pred = reg.predict(polynomial.fit_transform(X_test))
    MSE = mean_squared_error(Y_test, y_pred)
    MSE_train = mean_squared_error(Y_train, reg.predict(polynomial.fit_transform(X_train)))
    plt.figure('data' + str(degree))


    x = np.concatenate([X_test[0:10,:], X_train, X_test[10:, :]])
    y = np.concatenate([Y_test[0:10,:], Y_train, Y_test[10:, :]])

    y_pred = np.concatenate([y_pred[0:10,:], reg.predict(polynomial.fit_transform(X_train)), y_pred[10:,:]])
    plt.plot(x, y, '.')
    plt.plot(x, y_pred)
    #plt.show()
    print('-----------' + 'degree = ' + str(degree) + '-----------')
    print("Linear Regression coef:", reg.coef_)
    print("Linear Regression intercept:", reg.intercept_)
    print('Train Mean Square Error:', MSE_train)
    print("Test Mean Square Error:", MSE)


def myStandardScaler(X):
    mu = np.mean(X, axis=0, keepdims=True)
    std = np.std(X, axis=0, keepdims=True)
    epsilon = 1e-10
    X_norm = (X - mu) / (std + epsilon)
    return X_norm, mu, std

def GradientDescent(X_train, Y_train, X_test, Y_test, degree):
    np.random.seed()
    coeffs = np.random.normal(0, 1, degree)[:, np.newaxis]
    polynomial = PolynomialFeatures(degree=degree)
    X_transformed = polynomial.fit_transform(X_train)

    X_train_norm, mu_xtrain, std_xtrain = myStandardScaler(X_transformed[:,1:])
    Y_train_norm, mu_ytrain, std_ytrain = myStandardScaler(Y_train)

    lr = 0.1
    for i in range(50000):
        Err = -(Y_train_norm - np.sum(coeffs.T * X_train_norm, axis=1, keepdims=True))
        coeffs = coeffs - lr * (Err.T.dot(X_train_norm) / len(X_train_norm)).T
    coeffs_ = (coeffs.T / std_xtrain * std_ytrain).T
    bias = mu_ytrain - coeffs_.T.dot(mu_xtrain.T)


    X_transformed_test = polynomial.fit_transform(X_test)
    ypred_train = np.matmul(X_transformed[:,1:], coeffs_)+ bias
    ypred = np.matmul(X_transformed_test[:,1:], coeffs_)+ bias

    MSE_train = mean_squared_error(Y_train, ypred_train)
    MSE = mean_squared_error(Y_test, ypred)


    print('-----------' + 'degree = ' + str(degree) + '-----------')
    print("Linear Regression coef:", coeffs_)
    print("Linear Regression intercept:", bias)

    print('Train Mean Square Error:', MSE_train)
    print("Test Mean Square Error:", MSE)

    
def main():
    #plotcurve()
    X_train, Y_train, X_test, Y_test = Generate_Data(20, 80)

    print('------------------------Polyfit--------------------')
    for i in range(6):
        polyfit(i+1, X_train, Y_train, X_test, Y_test)
    print('------------------------Gradient Descent--------------------')
    for i in range(6):
        GradientDescent(X_train, Y_train, X_test, Y_test, i+1)
    print('1')
    
if __name__ == "__main__":
    main()