description('Test for event dispatching by spin buttons in a type=numnber input.');

var parent = document.createElement('div');
document.body.appendChild(parent);
parent.innerHTML = '<input type=number id=number value=0 max=1><input id=another>';
var numberInput = document.getElementById('number');
var anotherInput = document.getElementById('another');
var inputEventCounter = 0;
var changeEventCounter = 0;

numberInput.onchange = function() { changeEventCounter++; };
numberInput.oninput = function() { inputEventCounter++; };

if (window.eventSender) {
    debug('Initial state');
    shouldBe('changeEventCounter', '0');
    shouldBe('inputEventCounter', '0');

    debug('Click the upper button');
    // Move the cursor on the upper button.
    eventSender.mouseMoveTo(numberInput.offsetLeft + numberInput.offsetWidth - 4, numberInput.offsetTop + 4);
    eventSender.mouseDown();
    eventSender.mouseUp();
    shouldBe('numberInput.value', '"1"');
    shouldBe('changeEventCounter', '0');
    shouldBe('inputEventCounter', '1');

    debug('Click again, but the value is not changed.');
    eventSender.mouseDown();
    eventSender.mouseUp();
    shouldBe('numberInput.value', '"1"');
    shouldBe('changeEventCounter', '0');
    shouldBe('inputEventCounter', '1');

    debug('Focus on another field');
    anotherInput.focus();
    shouldBe('changeEventCounter', '1');
    shouldBe('inputEventCounter', '1');

    parent.innerHTML = '';
} else {
  document.getElementById('console').innerHTML = 'No eventSender';
}

var successfullyParsed = true;
