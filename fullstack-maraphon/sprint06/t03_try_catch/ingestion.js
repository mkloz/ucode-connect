class Ingestion {
  constructor(meal_type, day_of_diet) {
    this.id = Math.floor(Math.random() * 1000);
    this.meal_type = meal_type;
    this.day_of_diet = day_of_diet;
    this.products = [];
  }

  setProduct(product) {
    this.products.push(product);
  }

  getProductInfo(name) {
    return this.products.find((product) => product.name === name);
  }

  getFromFridge(productName) {
    const product = this.getProductInfo(productName);
    if (product.isJunkFood()) {
      throw new EatException(
        `Too many calories in ${productName} for breakfast`,
      );
    }
  }
}

module.exports = { Ingestion };
