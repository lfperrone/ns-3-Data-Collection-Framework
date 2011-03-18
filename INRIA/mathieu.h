

class Collector
{
public:  
  virtual void CollectDouble (std::string context, double value) = 0;
  virtual void CollectInt (std::string context, int64_t value) = 0;
};

class ProcessingCollector : public Collector
{
public:
  Ptr<Collector> GetParent (void);
  void SetParent (Ptr<Collector> collector);
private:
  Ptr<Collector> m_parent;
};

class MeanProcessingCollector : public ProcessingCollector
{
public:
  MeanProcessingCollector ();
private:
  virtual void CollectDouble (std::string context, double value) {
    m_dblMean ... ;
  }
  virtual void CollectInt (std::string context, int64_t value) {
  }
  double m_dblMean;
  int64_t m_intMean;
};


1) storage collector
no parent

2) processing
parent


user: 
context path, value, timestamp

there's a tree that starts from node and has branches that go through
objects ending in locations where probes live

there's another tree that has leaves where probes live, but which starts merging paths until it arrives at an aggregation point

paths in the second tree reflect the kind of processing that the values colected will undergo until they are reported for storage
-> nodes have pointers to parent and to children 

-> one might want to have record of ALL trace sources in a simulation model
-> can we have a default processing to apply to every trace source?
-> enable/disable controls propagate from one node down to the reachable leaves

output tree of processing collectors
(i) welford node - mean, stdev
(ii) window n node 
(iii) dynamic histogram
(iv) interarrival time of samples - doesn't take data, it can only be leaf

-> what if nodes report not point estimates, but confidence intervals with a certain L?
-> every 100 samples you report avg/stdev 

types of samples:
int
float
vector int - blobs of different bit lengths to represent vectors? long text mysql data type? is this the same as varchar? http://dev.mysql.com/doc/refman/5.0/en/char.html
vector float

nodes on the right of the tree might ask children nodes for data; that is, when we want to flush for termination

we want to have unique ids for probe/collector nodes; infer semantics of the data

-> when you report data to a parent, you report your node id
-> the root build a dynamic table of paths, where each path has a unique id
-> the construction of the collector tree defines the semantic of the recorded sample - we don't need a collector to pass to his parent the path of each sample it received for processing, it just passes the sample because by construction you defined that the guy computes an aggregate

-> we don't know what kind of processing people will want, so right now, we will make things generic at this time

-> 
we have paths for the first tree in the context strings; in establishing connections they are just called paths

we need a mechanism to record the paths in the second tree

-> nodes can work with push or pull semantics (notify parent, then parent retrieves the data)
