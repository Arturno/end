let dane = [];				/**< dane potrzebne do narysowania wykresu*/
let fileUploaded = false;	/**< flaga informujaca o poprawnym wczytaniu pliku*/
let parameters =[];			/**< tablica przechowujaca parametry testu*/
let measurements =[];		/**< tablica przechowujaca wyniki testu*/

//wczytanie dodatków do rysowania wykresów google
google.charts.load('current', {'packages':['corechart']});


//funkcje zajmujace sie wczytaniem i przetworzeniem pliku na tablice danych

//funkcja do pobrania pliku
function handleFiles(files) {
	parameters = [];
	measurements =[];
	var temp = files[0].name.split(".");
	if(temp[1] != "csv")
		displayError("File type")
	else if (window.FileReader) 
	{
		getAsText(files[0]);
		fileUploaded = true;
	}
	else 
	{
		displayError("FR");
	}
}	

//wczytanie pliku
function getAsText(fileToRead) {
  let reader = new FileReader();
  reader.readAsText(fileToRead);
  reader.onload = loadHandler;
  reader.onerror = errorHandler;
}

function loadHandler(event) {
  let csv = event.target.result;
  processData(csv);
}
//obsługa błędów
function errorHandler(evt) {
  if(evt.target.error.name == "NotReadableError") {
      displayError("NRE")
  }
}

//przekształcenie wartości z pliku na tekst i wpisanie ich do odpowiednich tabel
function processData(csv) {
	var data_type;
    let allTextLines = csv.split(/\r\n|\n/);
    for (let i=0; i<allTextLines.length; i++) {
		if(allTextLines[i]==="#PARAMETRY: ")
		{
			data_type = "PAR";
			continue;
		}
		else if(allTextLines[i]==="#POMIARY: ")
		{
			data_type = "POM";
			continue;
		}
        let data = allTextLines[i].split(';');
		var tarr = [];
            for (var j=0; j<data.length; j++) {
				if(data_type === "PAR")
				{tarr.push(data[j]);}
				else if(data_type === "POM")
				{
					if(isNaN(data[j]))
					{
					tarr.push(data[j]);
					}
					else{tarr.push(parseFloat(data[j]));}
				}
				}
			if(data_type === "PAR")
			{
			parameters.push(tarr);
			}
			else if(data_type === "POM")
			{
			measurements.push(tarr);
			}
	}
  arrayCreated = true;
  crtable();
}

//wyświetlenie parametrów testu
function displayParameters()	{
	if(!fileUploaded) 
	{
		displayError('No File');
    } 
	else if (parameters.length === 0) 
	{
		displayError('Empty');
    } 
	else 
	{
	var par = "<table class=\"table table-striped table-dark table-sm\">";
	for(var i = 0; i < parameters.length; i++)
	{
		par += "<tr>";
		for(var j = 0; j < parameters[i].length; j++){
			par += "<td>";
			par += parameters[i][j];
			par += "</td>";
		}
	  
		par += "</tr>";
	}
	par += "</table>";
	document.getElementById("param").innerHTML = par;
	}
}

//zbieranie danych od uzytkownika i tworzenie tabeli z danymi do rysowania wykresu
function collectDataToChart() {
	var x = document.forms["os"]["exampleRadios"].value;
	
	var y = [];
	if(document.getElementById("czas-y").checked)
	{
		y.push(document.getElementById("czas-y").value)
	};
	if(document.getElementById("polozenie-y").checked)
	{
		y.push(document.getElementById("polozenie-y").value)
	};
	if(document.getElementById("zadana-przepływność-y").checked)
	{
		y.push(document.getElementById("zadana-przepływność-y").value)
	};
	if(document.getElementById("przepływność-y").checked)
	{
		y.push(document.getElementById("przepływność-y").value)
	};
	if(document.getElementById("poziom-y").checked)
	{
		y.push(document.getElementById("poziom-y").value)
	};
	if(document.getElementById("jakosc-y").checked)
	{
		y.push(document.getElementById("jakosc-y").value)
	};
	if(document.getElementById("odebrane-y").checked)
	{
		y.push(document.getElementById("odebrane-y").value)
	};
	if(document.getElementById("stracone-y").checked)
	{
		y.push(document.getElementById("stracone-y").value)
	};
	if(document.getElementById("ber-y").checked)
	{
		y.push(document.getElementById("ber-y").value)
	};
	if(y.length === 0)
	{
		displayError("No y");
	}
	else if(!fileUploaded) 
	{
		displayError('No File');
    } 
	else if (parameters.length === 0) 
	{
		displayError('Empty');
    } 
	else 
	{
	for(var i = 1; i < measurements.length-1; i++){
		var tar =[];
		tar[0] = measurements[i][parseInt(x)]
		for( var a=1; a <= y.length; a++)
		{
		tar[a] = measurements[i][parseInt(y[a-1])]
		}
		tar[a] = NaN;
		tar[a+1] = "\nChannel: " + measurements[i][11].toString() + 
				   "\nBandwith: " + measurements[i][13].toString() +
				   "\nMCS: " + measurements[i][14].toString() +
				   "\nNSS: " + measurements[i][15].toString() + 
				   "\nSGI: " + measurements[i][16].toString();
		dane.push(tar)
	}
        drawChart(x,y);
    }
	dane =[];
}

//rysowanie wykresu 
function drawChart(x,y) {
        var dataTable = new google.visualization.DataTable();
        var options = {
          legend: 'none',
		  focusTarget: 'category',
		}
		dataTable.addColumn('number', measurements[0][parseInt(x)]);
		for(var a=1; a <= y.length; a++)
		{
			dataTable.addColumn('number', measurements[0][parseInt(y[a-1])]);
		}
		dataTable.addColumn('number' ,"Info");
		dataTable.addColumn({type: 'string', role: 'tooltip'});
		dataTable.addRows(dane);
        var chart = new google.visualization.LineChart(document.getElementById('chart'));
		
        chart.draw(dataTable, options);
    }

  
//tworzenie tabeli z pobranych danych
function crtable() {
	with(document.getElementById('tblh'))while(hasChildNodes())removeChild(firstChild);
	with(document.getElementById('tbl'))while(hasChildNodes())removeChild(firstChild);
	tblh = document.getElementById('tblh');
	//console.log(measurements);
	addHeader(tblh, measurements[0]);
	tbl = document.getElementById('tbl');
	for(var i = 1; i < measurements.length; i++)
	{
		addRow(tbl, measurements[i]);
	}
}

//dodawanie nagłówków do tabeli
function addHeader(tbl, row) {
	var tr = document.createElement('tr');
	//console.log(row);
	for(var i=0; i< row.length; i++)
	{
		var td = document.createElement('th');
		var tmp = row[i].split('_');
		if(tmp.length > 1)
			td.innerHTML = tmp[0] + " " + tmp[1];
		else 
			td.innerHTML = tmp[0];
		tr.appendChild(td)
	}
	tbl.appendChild(tr)
  }

//dodawanie wierszy do tabeli
function addRow(tbl, row) {
	var tr = document.createElement('tr');
	for(var i=0; i< row.length; i++)
	{
		addCell(tr, row[i]);
	}
	tbl.appendChild(tr)
  }

//dodawanie komórek do tabeli
 function addCell(tr, cell) {
    var td = document.createElement('td');

    td.innerHTML = cell;

    tr.appendChild(td)
  }

//wyświetlenie/ukrywanie tabeli po naciśnięciu przycisku
function showtable() {
	var x = document.getElementById("t");
	if (x.style.display === "none") {
		x.style.display = "block";
	} else {
		x.style.display = "none";
	}
}
//funkcja służąca do obsługi problemów
function displayError(errortext) {
    switch(errortext)
	{
		case 'File type':
		alert("Wrong file type.");
		break;
		case 'NRE':
		alert("Cannot read file!");
		break;
		case 'FR':
		alert("FileReader are not supported in this browser.")
		break;
		case 'No File':
		alert("No file uploaded")
		break;
		case 'Empty':
		alert("Loaded file is Empty")
		break;
		case 'No y':
		alert("No data to display specified")
		break;
	}
}