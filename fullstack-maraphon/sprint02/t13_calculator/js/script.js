function Calculator(num) {
    this.result = num || 0;
}

Calculator.prototype.init = function (num) {
    this.result = num;
    return this;
};

Calculator.prototype.add = function (num) {
    this.result += num;
    return this;
};

Calculator.prototype.sub = function (num) {
    this.result -= num;
    return this;
};

Calculator.prototype.mul = function (num) {
    this.result *= num;
    return this;
};

Calculator.prototype.div = function (num) {
    if (num !== 0) {
        this.result /= num;
    } else {
        console.log('Error: Division by zero.');
    }
    return this;
};

Calculator.prototype.alert = function () {
    setTimeout(() => {
        alert('Current result: ' + this.result);
    }, 5000);
    return this;
};
