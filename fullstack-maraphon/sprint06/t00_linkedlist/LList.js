class LList {
  constructor() {
    this.head = null;
  }

  getFirst() {
    return this.head ? this.head.data : null;
  }

  getLast() {
    let current = this.head;
    while (current && current.next) {
      current = current.next;
    }
    return current ? current.data : null;
  }

  add(value) {
    const newNode = new LLData(value);
    if (!this.head) {
      this.head = newNode;
    } else {
      let current = this.head;
      while (current.next) {
        current = current.next;
      }
      current.next = newNode;
    }
  }

  addFromArray(arrayOfData) {
    arrayOfData.forEach((value) => this.add(value));
  }

  remove(value) {
    if (!this.head) return;

    if (this.head.data === value) {
      this.head = this.head.next;
      return;
    }

    let current = this.head;
    while (current.next && current.next.data !== value) {
      current = current.next;
    }

    if (current.next) {
      current.next = current.next.next;
    }
  }

  removeAll(value) {
    while (this.head && this.head.data === value) {
      this.head = this.head.next;
    }

    let current = this.head;
    while (current && current.next) {
      if (current.next.data === value) {
        current.next = current.next.next;
      } else {
        current = current.next;
      }
    }
  }

  contains(value) {
    let current = this.head;
    while (current) {
      if (current.data === value) return true;
      current = current.next;
    }
    return false;
  }

  clear() {
    this.head = null;
  }

  count() {
    let count = 0;
    let current = this.head;
    while (current) {
      count++;
      current = current.next;
    }
    return count;
  }

  toString() {
    const elements = [];
    let current = this.head;
    while (current) {
      elements.push(current.data);
      current = current.next;
    }
    return elements.join(', ');
  }

  *getIterator() {
    let current = this.head;

    while (current) {
      yield current.data;
      current = current.next;
    }
  }

  [Symbol.iterator]() {
    return this.getIterator();
  }

  filter(callback) {
    const filteredList = new LList();
    let current = this.head;
    while (current) {
      if (callback(current.data)) {
        filteredList.add(current.data);
      }
      current = current.next;
    }
    return filteredList;
  }
}

module.exports = { LList };
