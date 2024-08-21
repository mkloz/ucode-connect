function getAnonymous(name, alias, affiliation) {
  return new (class {
    #name;
    #alias;
    #affiliation;

    constructor(name, alias, affiliation) {
      this.#name = name;
      this.#alias = alias;
      this.#affiliation = affiliation;
    }
    get name() {
      return this.#name;
    }
    get alias() {
      return this.#alias;
    }
    get affiliation() {
      return this.#affiliation;
    }
    set name(name) {
      return (this.#name = name);
    }
    set alias(alias) {
      return (this.#alias = alias);
    }
    set affiliation(affiliation) {
      return (this.#affiliation = affiliation);
    }
  })(name, alias, affiliation);
}

module.exports.getAnonymous = getAnonymous;
