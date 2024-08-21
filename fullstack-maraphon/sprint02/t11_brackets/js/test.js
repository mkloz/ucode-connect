describe('checkBrackets function', () => {
    it('should return -1 for undefined input', () => {
        assert.equal(checkBrackets(undefined), -1);
    });

    it('should return -1 for null input', () => {
        assert.equal(checkBrackets(null), -1);
    });

    it('should return 0 for empty string input', () => {
        assert.equal(checkBrackets(''), 0);
    });

    it('should return 0 for input without brackets', () => {
        assert.equal(checkBrackets('hello world'), 0);
    });

    it('should return 7 for input with only opening brackets', () => {
        assert.equal(checkBrackets('((((((('), 7);
    });

    it('should return 0 for a string with balanced brackets', () => {
        assert.equal(checkBrackets('()'), 0);
    });

    it('should return 0 for a string with no brackets', () => {
        assert.equal(checkBrackets('abc'), 0);
    });

    it('should return 1 for a string with one unmatched opening bracket', () => {
        assert.equal(checkBrackets('('), 1);
    });

    it('should return 1 for a string with one unmatched closing bracket', () => {
        assert.equal(checkBrackets(')'), 1);
    });

    it('should return 3 for a string with three unmatched closing brackets', () => {
        assert.equal(checkBrackets(')))'), 3);
    });

    it('should return 2 for a string with two unmatched opening brackets', () => {
        assert.equal(checkBrackets('(('), 2);
    });

    it('should return 1 for a string with two unmatched opening and one unmatched closing bracket', () => {
        assert.equal(checkBrackets('(()'), 1);
    });

    it('should return 0 for a string with two unmatched opening and two unmatched closing brackets', () => {
        assert.equal(checkBrackets('(())'), 0);
    });

    it('should return 4 for a string with four unmatched opening and two unmatched closing brackets', () => {
        assert.equal(checkBrackets('(((((())'), 4);
    });

    it('should return 5 for a string with four unmatched opening and three unmatched closing brackets', () => {
        assert.equal(checkBrackets('(((((())('), 5);
    });

    it('should return 1 for a string with one unmatched opening and one unmatched closing bracket', () => {
        assert.equal(checkBrackets('())'), 1);
    });
});
