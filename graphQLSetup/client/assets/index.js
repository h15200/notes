// FRONT END CODE //

const query = `
query {
  authors {
    name
    id
  }
}
`;

const ul = document.querySelector('#ul');

const options = {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({ query }),
};

fetch('/graphql', options)
  .then((raw) => raw.json())
  .then((res) => {
    res.data.authors.forEach((author) => {
      console.log(author.name);
      const li = document.createElement('li');
      li.innerText = author.name;
      ul.appendChild(li);
    });
  })
  .catch((err) => console.log(err));
