import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import FlatCard from 'components/FlatCard'

const styles = {
  projectCard: {
    height: 400,
    flex: 6,
  },
}

const ProjectActivity = props => (
  <FlatCard rootStyles={styles.projectCard}>Project Activity</FlatCard>
)

ProjectActivity.propTypes = {}
ProjectActivity.defaultProps = {}

export default Radium(ProjectActivity)
