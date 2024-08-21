function processImage() {
  var imageUrl = document.getElementById('imageUrl').value;
  var originalImage = document.getElementById('original-image');
  var squareImage = document.getElementById('square-image');
  var redChannel = document.getElementById('red-channel');
  var greenChannel = document.getElementById('green-channel');
  var blueChannel = document.getElementById('blue-channel');

  originalImage.src = imageUrl;

  var img = new Image();
  img.crossOrigin = 'Anonymous';
  img.onload = function () {
    var canvas = document.createElement('canvas');
    var ctx = canvas.getContext('2d');
    var size = Math.max(this.width, this.height);
    canvas.width = size;
    canvas.height = size;
    ctx.drawImage(this, (size - this.width) / 2, (size - this.height) / 2);
    squareImage.src = canvas.toDataURL();

    ctx.drawImage(this, 0, 0);
    var redData = ctx.getImageData(0, 0, size, size);
    for (var i = 0; i < redData.data.length; i += 4) {
      redData.data[i + 1] = 0;
      redData.data[i + 2] = 0;
    }
    ctx.putImageData(redData, 0, 0);
    redChannel.src = canvas.toDataURL();

    ctx.drawImage(this, 0, 0);
    var greenData = ctx.getImageData(0, 0, size, size);
    for (var i = 0; i < greenData.data.length; i += 4) {
      greenData.data[i] = 0;
      greenData.data[i + 2] = 0;
    }
    ctx.putImageData(greenData, 0, 0);
    greenChannel.src = canvas.toDataURL();

    ctx.drawImage(this, 0, 0);
    var blueData = ctx.getImageData(0, 0, size, size);
    for (var i = 0; i < blueData.data.length; i += 4) {
      blueData.data[i] = 0;
      blueData.data[i + 1] = 0;
    }
    ctx.putImageData(blueData, 0, 0);
    blueChannel.src = canvas.toDataURL();
  };
  img.src = imageUrl;
}
