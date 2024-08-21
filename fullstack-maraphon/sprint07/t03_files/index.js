const express = require('express');
const fs = require('fs');
const path = require('path');
const multer = require('multer');
const File = require('./File.js');
const FileList = require('./FileList.js');

const app = express();
const port = 3000;

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static(__dirname));
app.use(multer().none());

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.post('/', (req, res) => {
  const fileName = req.body.fileName;
  const fileContent = req.body.fileContent;
  const filePath = path.join(__dirname, 'tmp', fileName);

  try {
    fs.appendFileSync(filePath, fileContent);
  } catch (err) {
    console.error(err);
    return res.status(500).send('Failed to create file');
  }

  res.status(201).send('File created successfully');
});

app.get('/list', (req, res) => {
  const fileList = new FileList();
  res.json({ html: fileList.getHTMLList() });
});

app.get('/show', (req, res) => {
  const fileName = req.query.file;
  const file = new File(fileName);
  const content = file.read();
  res.json({ content });
});

app.delete('/delete', (req, res) => {
  const fileName = req.query.file;
  const filePath = path.join(__dirname, 'tmp', fileName);

  try {
    fs.unlinkSync(filePath);
    res.status(204).send();
  } catch (err) {
    console.error(err);
    res.status(500).send('Failed to delete file');
  }
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
