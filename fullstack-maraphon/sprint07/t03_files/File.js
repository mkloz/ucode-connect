const fs = require('fs');
const path = require('path');

class File {
  constructor(name) {
    this.dir = 'tmp';
    if (name.includes('')) {
      this.name = name;
    } else {
      this.name = name + '.txt';
    }
    this.filePath = path.join(this.dir, this.name);
  }

  create() {
    try {
      fs.mkdirSync(this.dir, { recursive: true });
    } catch (err) {
      console.error('Error creating directory:', err);
    }

    try {
      fs.writeFileSync(this.filePath, '');
    } catch (err) {
      console.error('Error creating file:', err);
    }
  }

  write(content) {
    try {
      fs.accessSync(this.filePath, fs.constants.R_OK);
    } catch (err) {
      this.create();
    }

    try {
      fs.appendFileSync(this.filePath, content);
    } catch (err) {
      console.error('Error writing to file:', err);
    }
  }

  read() {
    try {
      const data = fs.readFileSync(this.filePath, 'utf-8');
      return data ? data : 'File is Empty!';
    } catch (err) {
      console.error('Error reading file:', err);
      return 'No file information';
    }
  }

  delete() {
    try {
      fs.accessSync(this.filePath, fs.constants.R_OK);
      fs.rmSync(this.filePath);
    } catch (err) {
      console.error('Error deleting file:', err);
    }
  }
}

module.exports = File;
