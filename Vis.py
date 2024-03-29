import numpy as np
from bokeh.io import curdoc
from bokeh.layouts import row, column
from bokeh.models import ColumnDataSource
from bokeh.models.widgets import Slider, TextInput, Div
from bokeh.plotting import figure
import os
import sys
import time


file_name = sys.argv[1]
out_name = 'out.txt'
inp_points = np.loadtxt(fname=file_name,skiprows=1)
x_in = []
y_in = []
for point in inp_points:
    x_in.append(point[0])
    y_in.append(point[1])
plot = figure(plot_width = 400,plot_height = 400)
plot.circle(x_in,y_in,size = 5,color = 'navy',alpha = 0.5)

cost = Slider(title="Cost", value=0, start=0, end=100, step=1)
button_1 = Div(text="""Optimal cost value : """,width=200, height=100)
button_2 = Div(text="""Running time : """,width=200, height=100)
x = []
y = []
source = ColumnDataSource(data = dict(x = x,y = y))
plot.line('x','y',source = source,line_width = 3,line_alpha = 0.6)


def update_data(attrname, old, new):
	c = cost.value
	nan = float('nan')
	cmd = './a.out' + " " + str(c) +" > out.txt" + " < " + file_name
	start = time.time()
	os.system(cmd)
	end = time.time()
	x = []
	y = []
	i = 0
	out_points = np.loadtxt('out.txt',skiprows=1)
	if out_points.size != 4:
	    for point in out_points:
	        x.append(point[0])
	        y.append(point[1])
	        x.append(point[2])
	        y.append(point[3])
	        x.append(nan)
	        y.append(nan)
	        x.append(nan)
	        y.append(nan)
	else:
	    for point in out_points:
	        if i % 2 == 0:
	            x.append(point)
	        else:
	            y.append(point)
	        i += 1
	source.data = dict(x=x, y=y)
	output = "<b>Optimal cost value: </b> <p>"
	rtime = "<b> Running time: </b> <p>"
	with open("out.txt","r") as f:
		output+= f.readline()
		button_1.text = output
	rtime+=str((end-start))
	button_2.text = rtime
cost.on_change('value', update_data)


inputs = column(cost,button_1,button_2)
curdoc().add_root(row(inputs, plot, width=800))
curdoc().title = "Curve fitting"