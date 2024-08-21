module.exports = class Access {
  constructor(sign) {
    this._mark_LXXXV = sign;
  }

  get mark_LXXXV() {
    if (this._mark_LXXXV === undefined) return 'undefined';
    if (this._mark_LXXXV === null) return 'null';

    return this._mark_LXXXV;
  }
  set mark_LXXXV(sign) {
    this._mark_LXXXV = sign;
  }
};
