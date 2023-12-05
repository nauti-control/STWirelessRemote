function ConfigureSetupScreen() {

    // Configure Drop Down
    for (let i = 1; i <= 8; i++) {
        var dropdown = document.getElementById("button" + i + "act");
        AddButtonOptions(dropdown);
    }

    AddTimerOptions();
    GetDeviceOptions();

}

function GetDeviceOptions() {
    console.log("Getting Device Options");
    $.getJSON('/GetOptions.json', function (data) {
        
        SetOptions(data);
        var parentForm = document.getElementById("setupdiv");
        parentForm.style.visibility = "visible";
      
    });
}

async function PostDeviceOptions() {
    let form = document.getElementById("setupform");
    let setupDiv = document.getElementById("setupdiv");
    var loadingDiv = document.getElementById("savingdiv")
    setupDiv.style.visibility = "collapse";
    savingdiv.style.visibility = "collapse";
    // Post data using the Fetch API
    let response = await fetch(form.action, {
        method: form.method,
        body: new FormData(form),
    });
    setupDiv.style.visibility = "visible";
    savingdiv.style.visibility = "visible";

}

function SetOptions(data) {
    console.log(data);
    var dropdown1 = document.getElementById("button1act");
    dropdown1.value = data.button1opt;

    var dropdown2 = document.getElementById("button2act");
    dropdown2.value = data.button2opt;

    var dropdown3 = document.getElementById("button3act");
    dropdown3.value = data.button3opt;
    var dropdown4 = document.getElementById("button4act");
    dropdown4.value = data.button4opt;
    var dropdown5 = document.getElementById("button5act");
    dropdown5.value = data.button5opt;
    var dropdown6 = document.getElementById("button6act");
    dropdown6.value = data.button6opt;
    var dropdown7 = document.getElementById("button7act");
    dropdown7.value = data.button7opt;
    var dropdown8 = document.getElementById("button8act");
    dropdown8.value = data.button8opt;
    var dropdowntimermin = document.getElementById("timermin");
    dropdowntimermin.value = data.timermin;
    var dropdowntimersec = document.getElementById("timersec");
    dropdowntimersec.value = data.timersec;
  

}


function AddTimerOptions() {
    var minSelect = document.getElementById("timermin");
    for (let i = 0; i < 60; i++) {
        var option = document.createElement('option');
        option.value = i;
        option.innerHTML = i;
        minSelect.appendChild(option);
    }
    var secSelect = document.getElementById("timersec");
    for (let i = 0; i < 60; i++) {
        var option = document.createElement('option');
        option.value = i;
        option.innerHTML = i;
        secSelect.appendChild(option);
    }
}

async function SendControl(command) {

    let url = "/SendCommand.html?action=" + command;
    let response = await fetch(url);
}

function AddButtonOptions(dropdown) {

    var optMinus1 = document.createElement('option');
    optMinus1.value = 0;
    optMinus1.innerHTML = "Minus One";
    dropdown.appendChild(optMinus1);
    var optPlus1 = document.createElement('option');
    optPlus1.value = 1;
    optPlus1.innerHTML = "Plus One";
    dropdown.appendChild(optPlus1);
    var optMinus10 = document.createElement('option');
    optMinus10.value = 2;
    optMinus10.innerHTML = "Minus Ten";
    dropdown.appendChild(optMinus10);
    var optPlus10 = document.createElement('option');
    optPlus10.value = 3;
    optPlus10.innerHTML = "Plus Ten";
    dropdown.appendChild(optPlus10);
    var optAuto = document.createElement('option');
    optAuto.value = 4;
    optAuto.innerHTML = "Auto";
    dropdown.appendChild(optAuto);
    var optStandBy = document.createElement('option');
    optStandBy.value = 5;
    optStandBy.innerHTML = "Stand By";
    dropdown.appendChild(optStandBy);
    var optStartTimer = document.createElement('option');
    optStartTimer.value = 6;
    optStartTimer.innerHTML = "Start Timer";
    dropdown.appendChild(optStartTimer);

    var optWindMode = document.createElement('option');
    optWindMode.value = 7;
    optWindMode.innerHTML = "Wind Mode";
    dropdown.appendChild(optWindMode);
}
