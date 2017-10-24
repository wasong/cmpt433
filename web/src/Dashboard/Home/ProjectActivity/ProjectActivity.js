import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import FlatCard from 'components/FlatCard'
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
  <FlatCard rootStyles={styles.projectCard}>
    <div style={styles.title}>PROJECT ACTIVITY</div>
    <Divider />
    <List />
  </FlatCard>
)

ProjectActivity.propTypes = {}
ProjectActivity.defaultProps = {}

export default Radium(ProjectActivity)
