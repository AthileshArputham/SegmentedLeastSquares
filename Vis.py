import numpy as np
from bokeh.io import curdoc
from bokeh.layouts import row, column
from bokeh.models import ColumnDataSource
from bokeh.models.widgets import Slider, TextInput
from bokeh.plotting import figure
import os
import sys


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

cost = Slider(title="Cost", value=0, start=0, end=20, step=1)
x = []
y = []
source = ColumnDataSource(data = dict(x = x,y = y))
plot.line('x','y',source = source,line_width = 3,line_alpha = 0.6)


def update_data(attrname, old, new):
    c = cost.value
    nan = float('nan')
    cmd = './a.out' + " " + str(c) +" > out.txt" + " < " + file_name
    os.system(cmd)
    x = []
    y = []
    i = 0
    out_points = np.loadtxt('out.txt')
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

cost.on_change('value', update_data)


inputs = column(cost)
curdoc().add_root(row(inputs, plot, width=800))
curdoc().title = "Sliders"