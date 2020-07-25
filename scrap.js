// const string = 'hello patti';

// let array = string.match(/\W/g);
// console.log(array);
// let password = 'abc123';
// let posLook = /(?=ab)/;
// console.log(posLook.test(password)); //returns true

// const a = new Set([1, 1, 1, 2, 3]);
// console.log(a);
class Test {
  constructor(name) {
    this.name = name;
  }
  greet() {
    console.log('hi');
  }
}
const test = new Test('h');
console.log(test);

const Test2 = function (name) {
  this.name = name;
};
Test2.prototype.greet = function () {
  console.log('hi');
};

const test2 = new Test2('p');
test2.greet();
