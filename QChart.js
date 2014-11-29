// QChart.js ---
//
// Author: Julien Wintz
// Created: Thu Feb 13 14:37:26 2014 (+0100)
// Version:
// Last-Updated:
//           By:
//     Update #: 94
//

// Change Log:
//
//

var ChartType = {
         BAR: 1,
    DOUGHNUT: 2,
        LINE: 3,
         PIE: 4,
       POLAR: 5,
       RADAR: 6
};

var Chart = function(canvas, context) {

    var chart = this;

// /////////////////////////////////////////////////////////////////
// Pie helper
// /////////////////////////////////////////////////////////////////

    this.Pie = function(data,options) {

        chart.Pie.defaults = {
            segmentShowStroke: true,
            segmentStrokeColor: "#fff",
            segmentStrokeWidth: 2,
            animation: true,
            animationSteps: 100,
            animationEasing: "easeOutBounce",
            animateRotate: true,
            animateScale: false,
            onAnimationComplete: null
        };

        var config = (options)? mergeChartConfig(chart.Pie.defaults,options) : chart.Pie.defaults;

        return new Pie(data,config,context);
    };

// /////////////////////////////////////////////////////////////////
// Doughnut helper
// /////////////////////////////////////////////////////////////////

    this.Doughnut = function(data,options) {

        chart.Doughnut.defaults = {
            segmentShowStroke: true,
            segmentStrokeColor: "#fff",
            segmentStrokeWidth: 2,
            percentageInnerCutout: 50,
            animation: true,
            animationSteps: 100,
            animationEasing: "easeOutBounce",
            animateRotate: true,
            animateScale: false,
            onAnimationComplete: null
        };

        var config = (options)? mergeChartConfig(chart.Doughnut.defaults,options) : chart.Doughnut.defaults;

        return new Doughnut(data,config,context);

    };

// /////////////////////////////////////////////////////////////////
// Pie implementation
// /////////////////////////////////////////////////////////////////

    var Pie = function(data,config,ctx) {

        var segmentTotal = 0;
        var pieRadius = Min([height/2,width/2]) - 5;

        // /////////////////////////////////////////////////////////////////
        // initialisation
        // /////////////////////////////////////////////////////////////////

        this.init = function () {

            for (var i=0; i<data.length; i++) {
                segmentTotal += data[i].value;
            }
        }

        // /////////////////////////////////////////////////////////////////
        // drawing
        // /////////////////////////////////////////////////////////////////

        this.draw = function (progress) {

            clear(ctx);

            drawPieSegments(progress);
        }

        // ///////////////////////////////////////////////////////////////

        function drawPieSegments (animationDecimal) {

            var cumulativeAngle = -Math.PI/2,

            scaleAnimation = 1,
            rotateAnimation = 1;

            if (config.animation) {
                if (config.animateScale) {
                    scaleAnimation = animationDecimal;
                }
                if (config.animateRotate) {
                    rotateAnimation = animationDecimal;
                }
            }

            for (var i=0; i<data.length; i++) {
                var segmentAngle = rotateAnimation * ((data[i].value/segmentTotal) * (Math.PI*2));
                ctx.beginPath();
                ctx.arc(width/2,height/2,scaleAnimation * pieRadius,cumulativeAngle,cumulativeAngle + segmentAngle);
                ctx.lineTo(width/2,height/2);
                ctx.closePath();
                ctx.fillStyle = data[i].color;
                ctx.fill();

                if(config.segmentShowStroke) {
                    ctx.lineWidth = config.segmentStrokeWidth;
                    ctx.strokeStyle = config.segmentStrokeColor;
                    ctx.stroke();
                }
                cumulativeAngle += segmentAngle;
            }
        }
    }

// /////////////////////////////////////////////////////////////////
// Doughnut implementation
// /////////////////////////////////////////////////////////////////

    var Doughnut = function(data,config,ctx) {

        var segmentTotal = 0;
        var doughnutRadius = Min([height/2,width/2]) - 5;
        var cutoutRadius = doughnutRadius * (config.percentageInnerCutout/100);

        // /////////////////////////////////////////////////////////////////
        // initialisation
        // /////////////////////////////////////////////////////////////////

        this.init = function () {

            for (var i=0; i<data.length; i++) {
                segmentTotal += data[i].value;
            }
        }

        // /////////////////////////////////////////////////////////////////
        // drawing
        // /////////////////////////////////////////////////////////////////

        this.draw = function (progress) {

            clear(ctx);

            drawDoughnutSegments(progress);
        }

        // ///////////////////////////////////////////////////////////////

        function drawDoughnutSegments (animationDecimal) {

            var cumulativeAngle = -Math.PI/2,

            scaleAnimation = 1,
            rotateAnimation = 1;

            if (config.animation) {
                if (config.animateScale) {
                    scaleAnimation = animationDecimal;
                }
                if (config.animateRotate) {
                    rotateAnimation = animationDecimal;
                }
            }

            for (var i=0; i<data.length; i++) {
                var segmentAngle = rotateAnimation * ((data[i].value/segmentTotal) * (Math.PI*2));
                ctx.beginPath();
                ctx.arc(width/2,height/2,scaleAnimation * doughnutRadius,cumulativeAngle,cumulativeAngle + segmentAngle,false);
                ctx.arc(width/2,height/2,scaleAnimation * cutoutRadius,cumulativeAngle + segmentAngle,cumulativeAngle,true);
                ctx.closePath();
                ctx.fillStyle = data[i].color;
                ctx.fill();

                if(config.segmentShowStroke) {
                    ctx.lineWidth = config.segmentStrokeWidth;
                    ctx.strokeStyle = config.segmentStrokeColor;
                    ctx.stroke();
                }
                cumulativeAngle += segmentAngle;
            }
        }
    }

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

    var clear = function(c) {
        c.clearRect(0, 0, width, height);
    };


    function calculateOffset(val,calculatedScale,scaleHop) {

        var outerValue = calculatedScale.steps * calculatedScale.stepValue;
        var adjustedValue = val - calculatedScale.graphMin;
        var scalingFactor = CapValue(adjustedValue/outerValue,1,0);

        return (scaleHop*calculatedScale.steps) * scalingFactor;
    }

    function calculateScale(drawingHeight,maxSteps,minSteps,maxValue,minValue,labelTemplateString) {

        var graphMin,graphMax,graphRange,stepValue,numberOfSteps,valueRange,rangeOrderOfMagnitude,decimalNum;

        valueRange = maxValue - minValue;
        rangeOrderOfMagnitude = calculateOrderOfMagnitude(valueRange);
        graphMin = Math.floor(minValue / (1 * Math.pow(10, rangeOrderOfMagnitude))) * Math.pow(10, rangeOrderOfMagnitude);
        graphMax = Math.ceil(maxValue / (1 * Math.pow(10, rangeOrderOfMagnitude))) * Math.pow(10, rangeOrderOfMagnitude);
        graphRange = graphMax - graphMin;
        stepValue = Math.pow(10, rangeOrderOfMagnitude);
        numberOfSteps = Math.round(graphRange / stepValue);

        while(numberOfSteps < minSteps || numberOfSteps > maxSteps) {
            if (numberOfSteps < minSteps) {
                stepValue /= 2;
                numberOfSteps = Math.round(graphRange/stepValue);
            } else{
                stepValue *=2;
                numberOfSteps = Math.round(graphRange/stepValue);
            }
        };

        var labels = [];

        populateLabels(labelTemplateString, labels, numberOfSteps, graphMin, stepValue);

        return {
            steps: numberOfSteps,
            stepValue: stepValue,
            graphMin: graphMin,
            labels: labels
        }

        function calculateOrderOfMagnitude(val) {
            return Math.floor(Math.log(val) / Math.LN10);
        }
    }

    function populateLabels(labelTemplateString, labels, numberOfSteps, graphMin, stepValue) {
        if (labelTemplateString) {
            for (var i = 1; i < numberOfSteps + 1; i++) {
                labels.push(tmpl(labelTemplateString, {value: (graphMin + (stepValue * i)).toFixed(getDecimalPlaces(stepValue))}));
            }
        }
    }

    function Max(array) {
        return Math.max.apply(Math, array);
    };

    function Min(array) {
        return Math.min.apply(Math, array);
    };

    function Default(userDeclared,valueIfFalse) {
        if(!userDeclared) {
            return valueIfFalse;
        } else {
            return userDeclared;
        }
    };

    function isNumber(n) {
        return !isNaN(parseFloat(n)) && isFinite(n);
    }

    function CapValue(valueToCap, maxValue, minValue) {
        if(isNumber(maxValue)) {
            if( valueToCap > maxValue ) {
                return maxValue;
            }
        }
        if(isNumber(minValue)) {
            if ( valueToCap < minValue ) {
                return minValue;
            }
        }
        return valueToCap;
    }

    function getDecimalPlaces (num) {
        var numberOfDecimalPlaces;
        if (num%1!=0) {
            return num.toString().split(".")[1].length
        } else {
            return 0;
        }
    }

    function mergeChartConfig(defaults,userDefined) {
        var returnObj = {};
        for (var attrname in defaults) { returnObj[attrname] = defaults[attrname]; }
        for (var attrname in userDefined) { returnObj[attrname] = userDefined[attrname]; }
        return returnObj;
    }

    var cache = {};

    function tmpl(str, data) {
        var fn = !/\W/.test(str) ?
            cache[str] = cache[str] ||
            tmpl(document.getElementById(str).innerHTML) :

        new Function("obj",
                     "var p=[],print=function() {p.push.apply(p,arguments);};" +
                     "with(obj) {p.push('" +
                     str
                     .replace(/[\r\t\n]/g, " ")
                     .split("<%").join("\t")
                     .replace(/((^|%>)[^\t]*)'/g, "$1\r")
                     .replace(/\t=(.*?)%>/g, "',$1,'")
                     .split("\t").join("');")
                     .split("%>").join("p.push('")
                     .split("\r").join("\\'")
                     + "');}return p.join('');");

        return data ? fn( data ) : fn;
    };
}

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

/*!
 * Chart.js
 * http://chartjs.org/
 *
 * Copyright 2013 Nick Downie
 * Released under the MIT license
 * https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
 */

// Copyright (c) 2013 Nick Downie

// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
