const fs = require('fs');

class FileList {
  constructor() {
    this.dir = 'tmp';
    this.list = [];
    this.getList();
    fs.mkdirSync(this.dir, { recursive: true });
  }

  getList() {
    this.list = [];
    try {
      fs.accessSync(this.dir);
      const files = fs.readdirSync(this.dir, { withFileTypes: true });
      this.list = files
        .filter((file) => file.isFile())
        .map((file) => file.name);
    } catch (err) {
      console.error('Error reading directory:', err);
    }
    return this.list;
  }

  hasFiles() {
    return this.list.length > 0;
  }

  getHTMLList() {
    if (!this.list.length) return '';

    return `<ul>${this.list
      .map((item) => `<li data-file="${item}" class="btn-file">${item}</li>`)
      .join('')}</ul>`;
  }
}

module.exports = FileList;
