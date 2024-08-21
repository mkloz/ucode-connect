import { HardWorker } from './modules/hard-worker.js';

const worker = new HardWorker();
worker.name = 'Bruce';
worker.age = 50;
console.log(worker);
