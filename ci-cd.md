# CI/CD

devs often work in isolation and they need to integrate their changes with the rest of the team's code base. If the changes are simply on github, it's ok but when there are thousands of changes on a docker container, best practice is to test and merge seamlessly.

## CI = Continuous Integration

Philosophy and the practice of automating the integration of code change from multiple contributors into a single software project

Comprised of tools that assert the new code's correctness before integration.

## CD = Continuous Delivery / Deployment

## Delivery

Ensures code is always ihn a deployable state.
Automates the release of that validated code to a repo
Test automation and code release automation

## Delopyment

Automation of deployment of production code.

## CI/CD Benefits

Low risk releases
improve developer productivity
find and address bugs quicker
lower costs
faster time to market
better products

Big 3 are Travis CI, Cirlcle CI, and jenkins

## Travis CI - free for open source projects

A great first CI/CD application

comes with free hosting - no need to provide a dedicated server
resides on cloud - test projects in any env
build matrix - run tests with many different versions

- Pros
  fast start
  lightweight YAML config
  free plan for open source
  no dedicated server required

- CONS
  not flexible or customizable

  Travis can keep track of what's happening with github by listening via hooks, like the event emitter model.

  If the github attemps to merge a branch (by push or PRs), travis CI will get a merge hook and spin up a virtual image and run a series of tests. Only if the tests pass, the merge will continue.

## Jenkins

Self-contained - java-based program ready to run out of the box
update center - hundreds of plugins in the update center

- PROS
  free
  customization plugins system
  full control of the system

- CONS
  dedicated server needed
  time needed for configuration/customization
