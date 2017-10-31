import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import Divider from 'material-ui/Divider'

import List from './List'

const styles = {
  title: {
    fontSize: 18,
    margin: '0 0 5px',
    color: '#b1b1b1',
  },
  projectCard: {
    height: 500,
    flex: 6,
  },
}

const ProjectActivity = props => (
  <div>
    <div style={styles.title}>PROJECT ACTIVITY</div>
    <List />
  </div>
)

ProjectActivity.propTypes = {}
ProjectActivity.defaultProps = {}

export default Radium(ProjectActivity)
