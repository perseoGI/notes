# Docker Swarm

## References

- https://www.youtube.com/watch?v=dooPhkXT9yI
- https://www.youtube.com/watch?v=_F6PSP-qhdA
- https://speakerdeck.com/aluzzardi/heart-of-the-swarmkit-topology-management
- https://www.youtube.com/watch?v=EmePhjGnCXY
- http://thesecretlivesofdata.com/raft/


Swarm Mode is a clustering solution built inside Docker
It is not "classic Swarm" (pre-1.12)


We have two types of nodes:

- Manager: container with permissions to manage de swarm
    Managers are interconnected inside a Raft consensus group
    Managers have access to a Internal distributed state store (they all keep
    same copy). This stores all the configuration of the swarm
    Between managers, the traffic is encrypted.
    Each manager has a Certificate Authority which gives them the authority to
    manage the swarm
    Managers send orders down to the workers (managers could be workers also)
- Worker: simple container with a specific task

Docker swarm add new features:

- Replicas: tells how many instances of a container should run
- Scaling: impose conditions over when to scale up/down

A service will have some tasks, and a task will launch a container

Manager node:

- API: accept commands from client and creates service object
- Orchestrator: reconciliation loop for service objects and creates tasks
- Allocator: allocates IP addresses to tasks
- Scheduler: assigns nodes to tasks
- Dispatcher: checks in on workers

Worker node:

- Worker: connects to dispatcher to check on assigned tasks
- Executor: executes the tasks assigned to worker node


## swarm

### *init*

To initialite a swarm (check `docker info` to see if swarm in active)

    docker swarm init

It will create:
- Root Signing Certificate for the Swarm
- Certificate is issued for first manager node
- Join tokens
- Raft DB to store CA, configs and secrets
        - Encrypted by default
        - No need for another key/value system to hold orchestration/secrets
        - Replicate logs amongst managers via mutual TLS in control plane

## node

### *ls*

## service

Same as *run* for docker container

### *create*

Creates a new service

    docker service create alpine ping 8.8.8.8

### *ls*

List current services.
Replicas: number_instances_running/number_instances_should_run
Orchestrator shold focus on matching the numbers

### *ps*

Show containers running inside a service

    docker service ps <service_id>

### *update*

Edit cluster configuration on runtime

--replicas <num>: edit number of instances

This update command has more options than `docker container update` because
swarms are aimed to follow "blue/green" pattern, never take service down, but
replace and update containers on the fly.


If a container goes down, the swarm will relaunch new container
