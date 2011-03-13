#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#include <iostream>
#include <screen/utils/Profiler.h>
#include <screen/utils/ProfilerReporter.h>
#include <screen/utils/Logger.h>
#include <screen/utils/LoggerReporter.h>

int main(){
	SCREEN_ATTACH_LOGGER_REPORTER(new screen::utils::FileLoggerReporter("out.log"))
	SCREEN_ATTACH_PROFILE_REPORTER(new screen::utils::FileProfilerReporter("profiler.log"))
	
	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;
	
	// Add a listener that collects test result
	CPPUNIT_NS::TestResultCollector result;
	
	controller.addListener(&result);
	
	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	
	controller.addListener(&progress);
	
	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	runner.run(controller);
	
	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
	outputter.write();
	
	// Uncomment this for XML output
	std::ofstream file("cppunit-report.xml");
	
	CPPUNIT_NS::XmlOutputter xml(&result, file);
	
	xml.write();
	
	file.close();
	
	return 0;
}
