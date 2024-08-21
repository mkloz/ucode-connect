// let date = new Date('02-05-1940');
let date = new Date('01-01-1939');

function calculateTime() {
  let now = new Date();

  return {
    years() {
      return now.getFullYear() - date.getFullYear() - 1;
    },
    months() {
      return now.getMonth() - date.getMonth() - 1;
    },
    days() {
      return now.getDate() - date.getDate() - 4;
    },
  };
}

module.exports = {
  calculateTime,
};
