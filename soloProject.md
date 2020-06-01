<header>

# Discography 'GET', '/'

## Stretch Features - sort by, search, pagination

<button>create new data</button>
<label>Click to GET '/track' which is a page with a form with inputs and submit<label>

</header>
<table>
  <tr>
    <th>Id</th>
    <th>Track Name</th>
    <th>Type</th>
    <th>Artist</th>
    <th>Year Released</th>
    <th>Label</th>
    <th>Reference</th>
    <!-- <th>Instruments</th>
    <th>PPL</th>
    <th>IMDb</th>
    <th>Ref</th> -->

  </tr>
  <tr id="id", class="trackData">
    <td>required set by mongo</td>
    <td>required String input</td>
    <td>required String </td>
    <td>optional String input</td>
    <td>optional Number input between 1982 - current + 5</td>
    <td>optional String input</td>
    <td><button>Get more details</button></td>
    <!-- <td>radio buttons -  alto, tenor, bar, soprano, clar, bass clar, flute, picc, piano, composition, arranging</td>
    <td>Yes/No/n/a</td>
    <td>Yes/No/n/a</td>
    <td>comma separated urls</td> -->
    <td><button>edit - 'GET' '/track/id'</button></td>
    <td><button>delete RED - 'DELETE' '/track/id'</button></td> 
  </tr>
</table>

# GET, '/track' will be empty form. GET, 'track/id' will have form with current data populated inside the form

<form>
  <label>Track Name</label>
  <input type='text' />

  <p>Type</p>
  <input type="radio" name="type" value="music">
  <label for='music'>audio</label>
  <input type="radio" name="type" value="film score">
  <label for='film score'>film</label>
  <input type="radio" name="type" value="commercial jingle">
  <label for='commercial jingle'>jingle</label>
  <label for='other'>other</label>
  <input type="text" name="type">

<label>Artist</label>
<input type='text'/>

<label for="year">Year Released</label>
<input type="number" name="year"/>

<label for="label">Label</label>
<input type="number"/>

<p>Instruments used</p>
<input type="checkbox" name="clarinet" />
<label for="clarinet">Clarinet</label>
<input type="checkbox" name="bassCl" />
<label for="clarinet">Bass cl.</label>
<input type="checkbox" name="soprano" />
<label for="clarinet">Soprano sax</label>
<input type="checkbox" name="alto" />
<label for="clarinet">Alto sax</label>
<input type="checkbox" name="tenor" />
<label for="clarinet">Tenor sax</label>
<input type="checkbox" name="bari" />
<label for="clarinet">Bari sax</label>
<input type="checkbox" name="flute" />
<label for="clarinet">Flute</label>
<input type="checkbox" name="piccolo" />
<label for="clarinet">Piccolo</label>

<p>PPL (for audio only)</>
<input type="radio" name="ppl" value="yes">
<label for="ppl">Yes</label>
<input type="radio" name="ppl" value="no">
<label for="ppl">No</label>
<input type="radio" name="ppl" value="notApplicable">
<label for="ppl">N/a</label>

<p>IMDb</p>
<input type="radio" name="imdb" value="yes">
<label for="imdb">Yes</label>
<input type="radio" name="imdb" value="no">
<label for="imdb">No</label>
<input type="radio" name="imdb" value="notApplicable">
<label for="imdb">N/a</label>

<p>Youtube links</p>
<input type="text" name="url">
<input type="text" name="url">
<input type="text" name="url">

<button>Submit</button>

</form>
