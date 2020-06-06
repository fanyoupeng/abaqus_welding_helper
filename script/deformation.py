#删除热学属性
del mdb.models['Model-1'].materials['steel'].conductivity
del mdb.models['Model-1'].materials['steel'].density
del mdb.models['Model-1'].materials['steel'].latentHeat
del mdb.models['Model-1'].materials['steel'].specificHeat

#添加力学属性
#弹性
mdb.models['Model-1'].materials['steel'].Elastic(table=((200000.0, 0.29), ))
#塑性
mdb.models['Model-1'].materials['steel'].Plastic(temperatureDependency=ON, 
    table=((230.0, 0.0, 20.0), (235.0, 0.002, 20.0), (250.0, 0.1, 20.0), (
    180.0, 0.0, 600.0), (185.0, 0.002, 600.0), (190.0, 0.1, 600.0), (30.0, 0.0, 
    1000.0), (32.0, 0.002, 1000.0), (34.0, 0.1, 1000.0)))
#线膨胀系数
mdb.models['Model-1'].materials['steel'].Expansion(table=((1.2e-05, ), ))

#删除原有分析步
del mdb.models['Model-1'].steps['welding']
del mdb.models['Model-1'].steps['cooling']

#创建应力分析步
mdb.models['Model-1'].StaticStep(name='Step-1', previous='Initial', 
    timePeriod=12.5, maxNumInc=1000, initialInc=0.01, minInc=0.001, maxInc=0.1)
session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
mdb.models['Model-1'].StaticStep(name='Step-2', previous='Step-1', 
    timePeriod=600.0, maxNumInc=10000, initialInc=0.01, minInc=0.001, 
    maxInc=60.0)

#场输出
mdb.models['Model-1'].fieldOutputRequests['F-Output-1'].setValues(variables=(
    'S', 'E', 'U'))

#删除初始温度
del mdb.models['Model-1'].predefinedFields['init_temp']
#加载焊接温度

mdb.models['Model-1'].Temperature(name='Predefined Field-1', 
    createStepName='Step-1', distributionType=FROM_FILE, 
    fileName='D:\\Temp\\weld_thermal.odb', beginStep=1, beginIncrement=1, 
    endStep=1, endIncrement=1086, interpolate=OFF, 
    absoluteExteriorTolerance=0.0, exteriorTolerance=0.05)
mdb.models['Model-1'].predefinedFields['Predefined Field-1'].setValuesInStep(
    stepName='Step-2', beginStep=2, endStep=2, endIncrement=155)

#固定四点
v1=s = a.instances['instance_part'].vertices.findAt(((100,0,0),))
v2=s = a.instances['instance_part'].vertices.findAt(((-100,0,0),))
v3=s = a.instances['instance_part'].vertices.findAt(((100,0,100),))
v4=s = a.instances['instance_part'].vertices.findAt(((-100,0,100),))
region = a.Set(vertices=(v1,v2,v3,v4), name='Set-1')
mdb.models['Model-1'].EncastreBC(name='BC-4', createStepName='Initial', 
    region=region, localCsys=None)

#更改网格类型
elemType1 = mesh.ElemType(elemCode=C3D8R, elemLibrary=STANDARD)
p.setElementType(regions=(p.cells,), elemTypes=(elemType1,))

del mdb.jobs['weld_thermal']
mdb.Job(name='weld_deformation', model='Model-1', description='', type=ANALYSIS, 
    atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
    memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
    explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
    modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
    scratch='', resultsFormat=ODB, multiprocessingMode=DEFAULT, numCpus=1, 
    numGPUs=0)