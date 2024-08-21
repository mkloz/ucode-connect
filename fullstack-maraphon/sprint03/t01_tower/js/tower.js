class Building {
    constructor(floors, material, address) {
        this.floors = floors;
        this.material = material;
        this.address = address;
    }

    toString() {
        return `Floors: ${this.floors}\nMaterial: ${this.material}\nAddress: ${this.address}`;
    }
}

class Tower extends Building {
    constructor(floors, material, address) {
        super(floors, material, address);
        this.hasElevator = false;
        this.arcCapacity = null;
        this.height = null;
    }

    getFloorHeight() {
        if (this.height !== null && this.floors !== 0) {
            return this.height / this.floors;
        }
        return undefined;
    }

    toString() {
        return `${super.toString()}\nElevator: ${
            this.hasElevator ? '+' : '-'
        }\nArc reactor capacity: ${this.arcCapacity}\nHeight: ${
            this.height
        }\nFloor height: ${this.getFloorHeight()}`;
    }
}
