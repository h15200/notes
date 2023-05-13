// function debounce(cb, delay) {
//   let id = null;
//   return function (...args) {
//     if (id) {
//       clearTimeout(id);
//     }
//     id = setTimeout(() => {
//       cb.apply(null, args);
//     }, delay);
//   };
// }

// version 1

// function func1(name) {
//   console.log("name is", name);
// }

// const debouncer = debounce(func1, 2000);
//
// debouncer("patti");
// debouncer("lady");

function debounceWithCtx(cb, delay) {
  let id = null;
  return function (...args) {
    const ctx = this;
    if (id) {
      clearTimeout(id);
    }
    id = setTimeout(() => {
      cb.apply(ctx, args);
    }, delay);
  };
}

function sayName() {
  console.log("name is", this.name);
}

const obj = {
  name: "Yuma",
  cb: debounceWithCtx(sayName),
};

obj.cb();
