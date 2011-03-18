## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
	obj = bld.create_ns3_module('data-collection', ['node'])
	obj.source = [
	'collector.cc',
	'probe-factory.cc',
	'probe.cc',
	'probe-int.cc',
	'probe-helper.cc',
	]
	headers = bld.new_task_gen('ns3header')
	headers.module = 'data-collection'
	headers.source = [
	'collector.h',
	'probe-factory.h',
	'probe.h',
	'probe-int.h',
	'probe-helper.h',
	]
