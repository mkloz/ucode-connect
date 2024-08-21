document.addEventListener('DOMContentLoaded', () => {
  const content = document.getElementById('currentFile');
  const list = document.getElementById('fileList');

  if (content.innerHTML.length < 5) {
    content.classList.add('hide');
  }
  if (list.innerHTML.length < 5) {
    list.classList.add('hide');
  }

  const createForm = document.getElementById('createForm');
  createForm.addEventListener('submit', async (event) => {
    event.preventDefault();
    const formData = new FormData(createForm);
    try {
      const response = await fetch('/', {
        method: 'POST',
        body: formData,
      });
      if (response.ok) {
        getFileList();
        createForm.reset();
      } else {
        console.error('Failed to create file');
      }
    } catch (error) {
      console.error('Error:', error);
    }
  });

  const getFileList = async () => {
    try {
      const response = await fetch('/list');
      const data = await response.json();
      render(data);
    } catch (error) {
      console.error('Error:', error);
    }
  };

  const render = (data, name = '') => {
    if (data.html) {
      list.innerHTML = '<h2>Files:</h2>' + data.html;
      list.classList.remove('hide');
      document.querySelectorAll('.btn-file').forEach((item) => {
        item.addEventListener('click', (e) => showFile(e));
      });
    }
    if (data.content) {
      let render = '<h2>Selected file:</h2>';
      render += `<h2>${name}</h2>` + '<br>';
      render += data.content;
      render += `<div><button id="deletefile">Delete</button></div>`;
      content.innerHTML = render;
      content.classList.remove('hide');
      document.querySelector('#deletefile').addEventListener('click', () => {
        deleteFile(name);
      });
    }
  };

  const showFile = async (e) => {
    try {
      const response = await fetch('/show?file=' + e.target.dataset.file);
      const data = await response.json();
      render(data, e.target.dataset.file);
    } catch (error) {
      console.error('Error:', error);
    }
  };

  const deleteFile = async (fileName) => {
    try {
      const response = await fetch('/delete?file=' + fileName, {
        method: 'DELETE',
      });
      if (response.ok) {
        content.classList.add('hide');
        getFileList();
      } else {
        console.error('Failed to delete file');
      }
    } catch (error) {
      console.error('Error:', error);
    }
  };

  getFileList();
});
